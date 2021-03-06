/*
 * QTest TPM utilities
 *
 * Copyright (c) 2018 IBM Corporation
 * Copyright (c) 2018 Red Hat, Inc.
 *
 * Authors:
 *   Stefan Berger <stefanb@linux.vnet.ibm.com>
 *   Marc-André Lureau <marcandre.lureau@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */

#include "qemu/osdep.h"

#include "hw/acpi/tpm.h"
#include "libqtest.h"
#include "tpm-util.h"
#include "qapi/qmp/qdict.h"

#define TIS_REG(LOCTY, REG) \
    (TPM_TIS_ADDR_BASE + ((LOCTY) << 12) + REG)

static bool got_stop;

void tpm_util_crb_transfer(QTestState *s,
                           const unsigned char *req, size_t req_size,
                           unsigned char *rsp, size_t rsp_size)
{
    uint64_t caddr = qtest_readq(s, TPM_CRB_ADDR_BASE + A_CRB_CTRL_CMD_LADDR);
    uint64_t raddr = qtest_readq(s, TPM_CRB_ADDR_BASE + A_CRB_CTRL_RSP_ADDR);

    qtest_writeb(s, TPM_CRB_ADDR_BASE + A_CRB_LOC_CTRL, 1);

    qtest_memwrite(s, caddr, req, req_size);

    uint32_t sts, start = 1;
    uint64_t end_time = g_get_monotonic_time() + 5 * G_TIME_SPAN_SECOND;
    qtest_writel(s, TPM_CRB_ADDR_BASE + A_CRB_CTRL_START, start);
    while (true) {
        start = qtest_readl(s, TPM_CRB_ADDR_BASE + A_CRB_CTRL_START);
        if ((start & 1) == 0) {
            break;
        }
        if (g_get_monotonic_time() >= end_time) {
            break;
        }
    };
    start = qtest_readl(s, TPM_CRB_ADDR_BASE + A_CRB_CTRL_START);
    g_assert_cmpint(start & 1, ==, 0);
    sts = qtest_readl(s, TPM_CRB_ADDR_BASE + A_CRB_CTRL_STS);
    g_assert_cmpint(sts & 1, ==, 0);

    qtest_memread(s, raddr, rsp, rsp_size);
}

void tpm_util_tis_transfer(QTestState *s,
                           const unsigned char *req, size_t req_size,
                           unsigned char *rsp, size_t rsp_size)
{
    uint32_t sts;
    uint16_t bcount;
    size_t i;

    /* request use of locality 0 */
    qtest_writeb(s, TIS_REG(0, TPM_TIS_REG_ACCESS), TPM_TIS_ACCESS_REQUEST_USE);
    qtest_writel(s, TIS_REG(0, TPM_TIS_REG_STS), TPM_TIS_STS_COMMAND_READY);

    sts = qtest_readl(s, TIS_REG(0, TPM_TIS_REG_STS));
    bcount = (sts >> 8) & 0xffff;
    g_assert_cmpint(bcount, >=, req_size);

    /* transmit command */
    for (i = 0; i < req_size; i++) {
        qtest_writeb(s, TIS_REG(0, TPM_TIS_REG_DATA_FIFO), req[i]);
    }

    /* start processing */
    qtest_writeb(s, TIS_REG(0, TPM_TIS_REG_STS), TPM_TIS_STS_TPM_GO);

    uint64_t end_time = g_get_monotonic_time() + 50 * G_TIME_SPAN_SECOND;
    do {
        sts = qtest_readl(s, TIS_REG(0, TPM_TIS_REG_STS));
        if ((sts & TPM_TIS_STS_DATA_AVAILABLE) != 0) {
            break;
        }
    } while (g_get_monotonic_time() < end_time);

    sts = qtest_readl(s, TIS_REG(0, TPM_TIS_REG_STS));
    bcount = (sts >> 8) & 0xffff;

    memset(rsp, 0, rsp_size);
    for (i = 0; i < bcount; i++) {
        rsp[i] = qtest_readb(s, TIS_REG(0, TPM_TIS_REG_DATA_FIFO));
    }

    /* relinquish use of locality 0 */
    qtest_writeb(s, TIS_REG(0, TPM_TIS_REG_ACCESS),
                 TPM_TIS_ACCESS_ACTIVE_LOCALITY);
}

void tpm_util_startup(QTestState *s, tx_func *tx)
{
    unsigned char buffer[1024];
    unsigned char tpm_startup[] =
        "\x80\x01\x00\x00\x00\x0c\x00\x00\x01\x44\x00\x00";
    unsigned char tpm_startup_resp[] =
        "\x80\x01\x00\x00\x00\x0a\x00\x00\x00\x00";

    tx(s, tpm_startup, sizeof(tpm_startup), buffer, sizeof(buffer));

    g_assert_cmpmem(buffer, sizeof(tpm_startup_resp),
                    tpm_startup_resp, sizeof(tpm_startup_resp));
}

void tpm_util_pcrextend(QTestState *s, tx_func *tx)
{
    unsigned char buffer[1024];
    unsigned char tpm_pcrextend[] =
        "\x80\x02\x00\x00\x00\x41\x00\x00\x01\x82\x00\x00\x00\x0a\x00\x00"
        "\x00\x09\x40\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00"
        "\x0b\x74\x65\x73\x74\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00";

    unsigned char tpm_pcrextend_resp[] =
        "\x80\x02\x00\x00\x00\x13\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x01\x00\x00";

    tx(s, tpm_pcrextend, sizeof(tpm_pcrextend), buffer, sizeof(buffer));

    g_assert_cmpmem(buffer, sizeof(tpm_pcrextend_resp),
                    tpm_pcrextend_resp, sizeof(tpm_pcrextend_resp));
}

void tpm_util_pcrread(QTestState *s, tx_func *tx,
                      const unsigned char *exp_resp, size_t exp_resp_size)
{
    unsigned char buffer[1024];
    unsigned char tpm_pcrread[] =
        "\x80\x01\x00\x00\x00\x14\x00\x00\x01\x7e\x00\x00\x00\x01\x00\x0b"
        "\x03\x00\x04\x00";

    tx(s, tpm_pcrread, sizeof(tpm_pcrread), buffer, sizeof(buffer));

    g_assert_cmpmem(buffer, exp_resp_size, exp_resp, exp_resp_size);
}

static gboolean tpm_util_swtpm_has_tpm2(void)
{
    gint mystdout;
    gboolean succ;
    unsigned i;
    char buffer[10240];
    ssize_t n;
    gchar *swtpm_argv[] = {
        g_strdup("swtpm"), g_strdup("socket"), g_strdup("--help"), NULL
    };

    succ = g_spawn_async_with_pipes(NULL, swtpm_argv, NULL,
                                    G_SPAWN_SEARCH_PATH, NULL, NULL, NULL,
                                    NULL, &mystdout, NULL, NULL);
    if (!succ) {
        goto cleanup;
    }

    n = read(mystdout, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        goto cleanup;
    }
    buffer[n] = 0;
    if (!strstr(buffer, "--tpm2")) {
        succ = false;
    }

 cleanup:
    for (i = 0; swtpm_argv[i]; i++) {
        g_free(swtpm_argv[i]);
    }

    return succ;
}

gboolean tpm_util_swtpm_start(const char *path, GPid *pid,
                              SocketAddress **addr, GError **error)
{
    char *swtpm_argv_tpmstate = g_strdup_printf("dir=%s", path);
    char *swtpm_argv_ctrl = g_strdup_printf("type=unixio,path=%s/sock",
                                            path);
    gchar *swtpm_argv[] = {
        g_strdup("swtpm"), g_strdup("socket"),
        g_strdup("--tpmstate"), swtpm_argv_tpmstate,
        g_strdup("--ctrl"), swtpm_argv_ctrl,
        g_strdup("--tpm2"),
        NULL
    };
    gboolean succ;
    unsigned i;

    succ = tpm_util_swtpm_has_tpm2();
    if (!succ) {
        goto cleanup;
    }

    *addr = g_new0(SocketAddress, 1);
    (*addr)->type = SOCKET_ADDRESS_TYPE_UNIX;
    (*addr)->u.q_unix.path = g_build_filename(path, "sock", NULL);

    succ = g_spawn_async(NULL, swtpm_argv, NULL, G_SPAWN_SEARCH_PATH,
                         NULL, NULL, pid, error);

cleanup:
    for (i = 0; swtpm_argv[i]; i++) {
        g_free(swtpm_argv[i]);
    }

    return succ;
}

void tpm_util_swtpm_kill(GPid pid)
{
    int n;

    if (!pid) {
        return;
    }

    g_spawn_close_pid(pid);

    n = kill(pid, 0);
    if (n < 0) {
        return;
    }

    kill(pid, SIGKILL);
}

void tpm_util_migrate(QTestState *who, const char *uri)
{
    QDict *rsp;
    gchar *cmd;

    cmd = g_strdup_printf("{ 'execute': 'migrate',"
                          "'arguments': { 'uri': '%s' } }",
                          uri);
    rsp = qtest_qmp(who, cmd);
    g_free(cmd);
    g_assert(qdict_haskey(rsp, "return"));
    qobject_unref(rsp);
}

/*
 * Events can get in the way of responses we are actually waiting for.
 */
static QDict *tpm_util_wait_command(QTestState *who, const char *command)
{
    const char *event_string;
    QDict *response;

    response = qtest_qmp(who, command);

    while (qdict_haskey(response, "event")) {
        /* OK, it was an event */
        event_string = qdict_get_str(response, "event");
        if (!strcmp(event_string, "STOP")) {
            got_stop = true;
        }
        qobject_unref(response);
        response = qtest_qmp_receive(who);
    }
    return response;
}

void tpm_util_wait_for_migration_complete(QTestState *who)
{
    while (true) {
        QDict *rsp, *rsp_return;
        bool completed;
        const char *status;

        rsp = tpm_util_wait_command(who, "{ 'execute': 'query-migrate' }");
        rsp_return = qdict_get_qdict(rsp, "return");
        status = qdict_get_str(rsp_return, "status");
        completed = strcmp(status, "completed") == 0;
        g_assert_cmpstr(status, !=,  "failed");
        qobject_unref(rsp);
        if (completed) {
            return;
        }
        usleep(1000);
    }
}

void tpm_util_migration_start_qemu(QTestState **src_qemu,
                                   QTestState **dst_qemu,
                                   SocketAddress *src_tpm_addr,
                                   SocketAddress *dst_tpm_addr,
                                   const char *miguri,
                                   const char *ifmodel)
{
    char *src_qemu_args, *dst_qemu_args;

    src_qemu_args = g_strdup_printf(
        "-chardev socket,id=chr,path=%s "
        "-tpmdev emulator,id=dev,chardev=chr "
        "-device %s,tpmdev=dev ",
        src_tpm_addr->u.q_unix.path, ifmodel);

    *src_qemu = qtest_init(src_qemu_args);

    dst_qemu_args = g_strdup_printf(
        "-chardev socket,id=chr,path=%s "
        "-tpmdev emulator,id=dev,chardev=chr "
        "-device %s,tpmdev=dev "
        "-incoming %s",
        dst_tpm_addr->u.q_unix.path,
        ifmodel, miguri);

    *dst_qemu = qtest_init(dst_qemu_args);

    free(src_qemu_args);
    free(dst_qemu_args);
}
