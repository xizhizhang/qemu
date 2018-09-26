/*
 * CSKY helper
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

DEF_HELPER_2(exception, void, env, i32)
DEF_HELPER_1(brev, i32, i32)
DEF_HELPER_1(ff1, i32, i32)
DEF_HELPER_2(tb_trace, void, env, i32)
DEF_HELPER_3(jcount, void, env, i32, i32)
DEF_HELPER_3(csky_trace_icount, void, env, i32, i32)
DEF_HELPER_2(trace_tb_start, void, env, i32)
DEF_HELPER_2(trace_tb_exit, void, i32, i32)
DEF_HELPER_4(trace_ld8u, void, env, i32, i32, i32)
DEF_HELPER_4(trace_ld16u, void, env, i32, i32, i32)
DEF_HELPER_4(trace_ld32u, void, env, i32, i32, i32)
DEF_HELPER_4(trace_ld8s, void, env, i32, i32, i32)
DEF_HELPER_4(trace_ld16s, void, env, i32, i32, i32)
DEF_HELPER_4(trace_ld32s, void, env, i32, i32, i32)
DEF_HELPER_4(trace_st8, void, env, i32, i32, i32)
DEF_HELPER_4(trace_st16, void, env, i32, i32, i32)
DEF_HELPER_4(trace_st32, void, env, i32, i32, i32)
DEF_HELPER_5(trace_m_addr, void, env, i32, i32, i32, i32)
DEF_HELPER_4(trace_m_value, void, env, i32, i32, i32)
DEF_HELPER_1(trace_update_tcr, void, env)
#ifndef CONFIG_USER_ONLY
DEF_HELPER_1(rte, void, env)
DEF_HELPER_1(rfi, void, env)
DEF_HELPER_1(stop, void, env)
DEF_HELPER_1(wait, void, env)
DEF_HELPER_1(doze, void, env)
DEF_HELPER_2(psrclr, void, env, i32)
DEF_HELPER_2(psrset, void, env, i32)

DEF_HELPER_1(mfcr_cr0, i32, env)
DEF_HELPER_1(mfcr_cr20, i32, env)
#if defined(TARGET_CSKYV2)
DEF_HELPER_1(mfcr_cr15, i32, env)
DEF_HELPER_1(mfcr_cr28, i32, env)
DEF_HELPER_1(mfcr_cr29, i32, env)
DEF_HELPER_1(mfcr_cr30, i32, env)
DEF_HELPER_1(mfcr_cr31, i32, env)
DEF_HELPER_2(mfcr_mptimer, i32, env, i32)
DEF_HELPER_2(mtcr_cr15, void, env, i32)
DEF_HELPER_2(mtcr_cr28, void, env, i32)
DEF_HELPER_2(mtcr_cr29, void, env, i32)
DEF_HELPER_2(mtcr_cr31, void, env, i32)
DEF_HELPER_3(mtcr_mptimer, void, env, i32, i32)
#endif
DEF_HELPER_2(mtcr_cr0, void, env, i32)
DEF_HELPER_2(mtcr_cr18, void, env, i32)
DEF_HELPER_2(mtcr_cr20, void, env, i32)
DEF_HELPER_2(meh_write, void, env, i32)
DEF_HELPER_2(mcir_write, void, env, i32)
#endif

#if defined(TARGET_CSKYV1)
DEF_HELPER_1(cprc, void, env)
DEF_HELPER_1(cpwir, void, env)
#else /* TARGET_CSKYV2* */

#ifndef CONFIG_USER_ONLY
DEF_HELPER_1(wsc, void, env)
DEF_HELPER_1(tee_mfcr_cr19, i32, env)
DEF_HELPER_2(tee_mtcr_cr19, void, env, i32)
DEF_HELPER_3(mp_tlb_inv, void, env, i32, i32)
#endif

DEF_HELPER_1(ff0, i32, i32)

DEF_HELPER_3(xsr, i32, env, i32, i32)

DEF_HELPER_1(vfp_update_fcr, void, env)
DEF_HELPER_1(vfp_check_exception, void, env)

DEF_HELPER_3(vfp_adds, f32, f32, f32, env)
DEF_HELPER_3(vfp_addd, f64, f64, f64, env)
DEF_HELPER_3(vfp_subs, f32, f32, f32, env)
DEF_HELPER_3(vfp_subd, f64, f64, f64, env)
DEF_HELPER_3(vfp_muls, f32, f32, f32, env)
DEF_HELPER_3(vfp_muld, f64, f64, f64, env)
DEF_HELPER_3(vfp_divs, f32, f32, f32, env)
DEF_HELPER_3(vfp_divd, f64, f64, f64, env)
DEF_HELPER_1(vfp_negs, f32, f32)
DEF_HELPER_1(vfp_negd, f64, f64)
DEF_HELPER_1(vfp_abss, f32, f32)
DEF_HELPER_1(vfp_absd, f64, f64)
DEF_HELPER_2(vfp_sqrts, f32, f32, env)
DEF_HELPER_2(vfp_sqrtd, f64, f64, env)
DEF_HELPER_2(vfp_recips, f32, f32, env)
DEF_HELPER_2(vfp_recipd, f64, f64, env)

DEF_HELPER_3(vfp_cmp_ges, void, f32, f32, env)
DEF_HELPER_3(vfp_cmp_ged, void, f64, f64, env)
DEF_HELPER_3(vfp_cmp_ls, void, f32, f32, env)
DEF_HELPER_3(vfp_cmp_ld, void, f64, f64, env)
DEF_HELPER_3(vfp_cmp_lss, void, f32, f32, env)
DEF_HELPER_3(vfp_cmp_lsd, void, f64, f64, env)
DEF_HELPER_3(vfp_cmp_nes, void, f32, f32, env)
DEF_HELPER_3(vfp_cmp_ned, void, f64, f64, env)
DEF_HELPER_3(vfp_cmp_isNANs, void, f32, f32, env)
DEF_HELPER_3(vfp_cmp_isNANd, void, f64, f64, env)

DEF_HELPER_4(vfp_fmovis, f32, i32, i32, i32, env)
DEF_HELPER_4(vfp_fmovid, f64, i32, i32, i32, env)
DEF_HELPER_2(vfp_tosirns, f32, f32, env)
DEF_HELPER_2(vfp_tosirnd, f32, f64, env)
DEF_HELPER_2(vfp_tosirzs, f32, f32, env)
DEF_HELPER_2(vfp_tosirzd, f32, f64, env)
DEF_HELPER_2(vfp_tosirpis, f32, f32, env)
DEF_HELPER_2(vfp_tosirpid, f32, f64, env)
DEF_HELPER_2(vfp_tosirnis, f32, f32, env)
DEF_HELPER_2(vfp_tosirnid, f32, f64, env)
DEF_HELPER_2(vfp_touirns, f32, f32, env)
DEF_HELPER_2(vfp_touirnd, f32, f64, env)
DEF_HELPER_2(vfp_touirzs, f32, f32, env)
DEF_HELPER_2(vfp_touirzd, f32, f64, env)
DEF_HELPER_2(vfp_touirpis, f32, f32, env)
DEF_HELPER_2(vfp_touirpid, f32, f64, env)
DEF_HELPER_2(vfp_touirnis, f32, f32, env)
DEF_HELPER_2(vfp_touirnid, f32, f64, env)

DEF_HELPER_2(vfp_uitos, f32, f32, env)
DEF_HELPER_2(vfp_uitod, f64, f32, env)
DEF_HELPER_2(vfp_sitos, f32, f32, env)
DEF_HELPER_2(vfp_sitod, f64, f32, env)

DEF_HELPER_2(vfp_tods, f64, f32, env)
DEF_HELPER_2(vfp_tosd, f32, f64, env)

#ifndef CONFIG_USER_ONLY
DEF_HELPER_1(mfcr_cr14, i32, env)
DEF_HELPER_1(mfcr_cpidr, i32, env)

DEF_HELPER_2(mtcr_cr14, void, env, i32)
DEF_HELPER_2(mtcr_cr17, void, env, i32)
#endif

/* declear fpu v2 ISA helpers */
DEF_HELPER_2(fpu3_faddh, void, env, i32)
DEF_HELPER_2(fpu3_fsubh, void, env, i32)
DEF_HELPER_2(fpu3_fmovh, void, env, i32)
DEF_HELPER_2(fpu3_fabsh, void, env, i32)
DEF_HELPER_2(fpu3_fnegh, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzhsh, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzlth, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzneh, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzuoh, void, env, i32)
DEF_HELPER_2(fpu3_fcmphsh, void, env, i32)
DEF_HELPER_2(fpu3_fcmplth, void, env, i32)
DEF_HELPER_2(fpu3_fcmpneh, void, env, i32)
DEF_HELPER_2(fpu3_fcmpuoh, void, env, i32)
DEF_HELPER_2(fpu3_fmaxnm16, void, env, i32)
DEF_HELPER_2(fpu3_fminnm16, void, env, i32)
DEF_HELPER_2(fpu3_fcmphz16, void, env, i32)
DEF_HELPER_2(fpu3_fcmplsz16, void, env, i32)
DEF_HELPER_2(fpu3_fmulh, void, env, i32)
DEF_HELPER_2(fpu3_fnmulh, void, env, i32)
DEF_HELPER_2(fpu3_fmach, void, env, i32)
DEF_HELPER_2(fpu3_fmsch, void, env, i32)
DEF_HELPER_2(fpu3_fnmach, void, env, i32)
DEF_HELPER_2(fpu3_fnmsch, void, env, i32)
DEF_HELPER_2(fpu3_ffmula16, void, env, i32)
DEF_HELPER_2(fpu3_ffmuls16, void, env, i32)
DEF_HELPER_2(fpu3_ffnmula16, void, env, i32)
DEF_HELPER_2(fpu3_ffnmuls16, void, env, i32)
DEF_HELPER_2(fpu3_fdivh, void, env, i32)
DEF_HELPER_2(fpu3_freciph, void, env, i32)
DEF_HELPER_2(fpu3_fsqrth, void, env, i32)
DEF_HELPER_2(fpu3_fsel16, void, env, i32)

DEF_HELPER_2(fpu3_fadds, void, env, i32)
DEF_HELPER_2(fpu3_fsubs, void, env, i32)
DEF_HELPER_2(fpu3_fmovs, void, env, i32)
DEF_HELPER_2(fpu3_fabss, void, env, i32)
DEF_HELPER_2(fpu3_fnegs, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzhss, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzlts, void, env, i32)
DEF_HELPER_2(fpu3_fcmpznes, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzuos, void, env, i32)
DEF_HELPER_2(fpu3_fcmphss, void, env, i32)
DEF_HELPER_2(fpu3_fcmplts, void, env, i32)
DEF_HELPER_2(fpu3_fcmpnes, void, env, i32)
DEF_HELPER_2(fpu3_fcmpuos, void, env, i32)
DEF_HELPER_2(fpu3_fmaxnm32, void, env, i32)
DEF_HELPER_2(fpu3_fminnm32, void, env, i32)
DEF_HELPER_2(fpu3_fcmphz32, void, env, i32)
DEF_HELPER_2(fpu3_fcmplsz32, void, env, i32)
DEF_HELPER_2(fpu3_fmuls, void, env, i32)
DEF_HELPER_2(fpu3_fnmuls, void, env, i32)
DEF_HELPER_2(fpu3_fmacs, void, env, i32)
DEF_HELPER_2(fpu3_fmscs, void, env, i32)
DEF_HELPER_2(fpu3_fnmacs, void, env, i32)
DEF_HELPER_2(fpu3_fnmscs, void, env, i32)
DEF_HELPER_2(fpu3_ffmula32, void, env, i32)
DEF_HELPER_2(fpu3_ffmuls32, void, env, i32)
DEF_HELPER_2(fpu3_ffnmula32, void, env, i32)
DEF_HELPER_2(fpu3_ffnmuls32, void, env, i32)
DEF_HELPER_2(fpu3_fdivs, void, env, i32)
DEF_HELPER_2(fpu3_frecips, void, env, i32)
DEF_HELPER_2(fpu3_fsqrts, void, env, i32)
DEF_HELPER_2(fpu3_fsel32, void, env, i32)
DEF_HELPER_2(fpu3_fins32, void, env, i32)

DEF_HELPER_2(fpu3_faddd, void, env, i32)
DEF_HELPER_2(fpu3_fsubd, void, env, i32)
DEF_HELPER_2(fpu3_fmovd, void, env, i32)
DEF_HELPER_2(fpu3_fmovx32, void, env, i32)
DEF_HELPER_2(fpu3_fabsd, void, env, i32)
DEF_HELPER_2(fpu3_fnegd, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzhsd, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzltd, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzned, void, env, i32)
DEF_HELPER_2(fpu3_fcmpzuod, void, env, i32)
DEF_HELPER_2(fpu3_fcmphsd, void, env, i32)
DEF_HELPER_2(fpu3_fcmpltd, void, env, i32)
DEF_HELPER_2(fpu3_fcmpned, void, env, i32)
DEF_HELPER_2(fpu3_fcmpuod, void, env, i32)
DEF_HELPER_2(fpu3_fmaxnm64, void, env, i32)
DEF_HELPER_2(fpu3_fminnm64, void, env, i32)
DEF_HELPER_2(fpu3_fcmphz64, void, env, i32)
DEF_HELPER_2(fpu3_fcmplsz64, void, env, i32)
DEF_HELPER_2(fpu3_fmuld, void, env, i32)
DEF_HELPER_2(fpu3_fnmuld, void, env, i32)
DEF_HELPER_2(fpu3_fmacd, void, env, i32)
DEF_HELPER_2(fpu3_fmscd, void, env, i32)
DEF_HELPER_2(fpu3_fnmacd, void, env, i32)
DEF_HELPER_2(fpu3_fnmscd, void, env, i32)
DEF_HELPER_2(fpu3_ffmula64, void, env, i32)
DEF_HELPER_2(fpu3_ffmuls64, void, env, i32)
DEF_HELPER_2(fpu3_ffnmula64, void, env, i32)
DEF_HELPER_2(fpu3_ffnmuls64, void, env, i32)
DEF_HELPER_2(fpu3_fdivd, void, env, i32)
DEF_HELPER_2(fpu3_frecipd, void, env, i32)
DEF_HELPER_2(fpu3_fsqrtd, void, env, i32)
DEF_HELPER_2(fpu3_fsel64, void, env, i32)

DEF_HELPER_2(fpu3_fstosirn, void, env, i32)
DEF_HELPER_2(fpu3_fstosirz, void, env, i32)
DEF_HELPER_2(fpu3_fstosirpi, void, env, i32)
DEF_HELPER_2(fpu3_fstosirni, void, env, i32)
DEF_HELPER_2(fpu3_fstouirn, void, env, i32)
DEF_HELPER_2(fpu3_fstouirz, void, env, i32)
DEF_HELPER_2(fpu3_fstouirpi, void, env, i32)
DEF_HELPER_2(fpu3_fstouirni, void, env, i32)
DEF_HELPER_2(fpu3_fdtosirn, void, env, i32)
DEF_HELPER_2(fpu3_fdtosirz, void, env, i32)
DEF_HELPER_2(fpu3_fdtosirpi, void, env, i32)
DEF_HELPER_2(fpu3_fdtosirni, void, env, i32)
DEF_HELPER_2(fpu3_fdtouirn, void, env, i32)
DEF_HELPER_2(fpu3_fdtouirz, void, env, i32)
DEF_HELPER_2(fpu3_fdtouirpi, void, env, i32)
DEF_HELPER_2(fpu3_fdtouirni, void, env, i32)
DEF_HELPER_2(fpu3_fhtosirn, void, env, i32)
DEF_HELPER_2(fpu3_fhtosirz, void, env, i32)
DEF_HELPER_2(fpu3_fhtosirpi, void, env, i32)
DEF_HELPER_2(fpu3_fhtosirni, void, env, i32)
DEF_HELPER_2(fpu3_fhtouirn, void, env, i32)
DEF_HELPER_2(fpu3_fhtouirz, void, env, i32)
DEF_HELPER_2(fpu3_fhtouirpi, void, env, i32)
DEF_HELPER_2(fpu3_fhtouirni, void, env, i32)
DEF_HELPER_2(fpu3_fsitos, void, env, i32)
DEF_HELPER_2(fpu3_fuitos, void, env, i32)
DEF_HELPER_2(fpu3_fhtos, void, env, i32)
DEF_HELPER_2(fpu3_fstoh, void, env, i32)
DEF_HELPER_2(fpu3_fsitod, void, env, i32)
DEF_HELPER_2(fpu3_fuitod, void, env, i32)
DEF_HELPER_2(fpu3_fdtos, void, env, i32)
DEF_HELPER_2(fpu3_fstod, void, env, i32)
DEF_HELPER_2(fpu3_fmfvrh, void, env, i32)
DEF_HELPER_2(fpu3_fmfvrl, void, env, i32)
DEF_HELPER_2(fpu3_fmtvrh, void, env, i32)
DEF_HELPER_2(fpu3_fmtvrl, void, env, i32)
DEF_HELPER_2(fpu3_fmfvr64, void, env, i32)
DEF_HELPER_2(fpu3_fmfvr16, void, env, i32)
DEF_HELPER_2(fpu3_fmfvr322, void, env, i32)
DEF_HELPER_2(fpu3_fmtvr64, void, env, i32)
DEF_HELPER_2(fpu3_fmtvr16, void, env, i32)
DEF_HELPER_2(fpu3_fmtvr322, void, env, i32)

DEF_HELPER_2(fpu3_fldh, void, env, i32)
DEF_HELPER_2(fpu3_fsth, void, env, i32)
DEF_HELPER_2(fpu3_fldrh, void, env, i32)
DEF_HELPER_2(fpu3_fstrh, void, env, i32)
DEF_HELPER_2(fpu3_fldmh, void, env, i32)
DEF_HELPER_2(fpu3_fstmh, void, env, i32)
DEF_HELPER_2(fpu3_flrwh, void, env, i32)
DEF_HELPER_2(fpu3_fldmuh, void, env, i32)
DEF_HELPER_2(fpu3_fstmuh, void, env, i32)
DEF_HELPER_2(fpu3_flds, void, env, i32)
DEF_HELPER_2(fpu3_fsts, void, env, i32)
DEF_HELPER_2(fpu3_fldrs, void, env, i32)
DEF_HELPER_2(fpu3_fstrs, void, env, i32)
DEF_HELPER_2(fpu3_fldms, void, env, i32)
DEF_HELPER_2(fpu3_fstms, void, env, i32)
DEF_HELPER_2(fpu3_flrws, void, env, i32)
DEF_HELPER_2(fpu3_fldmus, void, env, i32)
DEF_HELPER_2(fpu3_fstmus, void, env, i32)
DEF_HELPER_2(fpu3_fldd, void, env, i32)
DEF_HELPER_2(fpu3_fstd, void, env, i32)
DEF_HELPER_2(fpu3_fldrd, void, env, i32)
DEF_HELPER_2(fpu3_fstrd, void, env, i32)
DEF_HELPER_2(fpu3_fldmd, void, env, i32)
DEF_HELPER_2(fpu3_fstmd, void, env, i32)
DEF_HELPER_2(fpu3_flrwd, void, env, i32)
DEF_HELPER_2(fpu3_fldmud, void, env, i32)
DEF_HELPER_2(fpu3_fstmud, void, env, i32)

DEF_HELPER_2(fpu3_fldm, void, env, i32)
DEF_HELPER_2(fpu3_fstm, void, env, i32)
DEF_HELPER_2(fpu3_fldrm, void, env, i32)
DEF_HELPER_2(fpu3_fstrm, void, env, i32)
DEF_HELPER_2(fpu3_fldmm, void, env, i32)
DEF_HELPER_2(fpu3_fstmm, void, env, i32)

DEF_HELPER_2(fpu3_fftox, void, env, i32)
DEF_HELPER_2(fpu3_fxtof, void, env, i32)
DEF_HELPER_2(fpu3_fftoi, void, env, i32)
DEF_HELPER_2(fpu3_fitof, void, env, i32)
DEF_HELPER_2(fpu3_fftofi, void, env, i32)
DEF_HELPER_2(fpu3_fmovi, void, env, i32)
#endif /* TARGET_CSKYV* */

