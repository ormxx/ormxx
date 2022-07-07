#ifndef ORMXX_INTERNAL_MACROS_UTILITY_H
#define ORMXX_INTERNAL_MACROS_UTILITY_H

#define __ORMXX_STR(x) #x

#define __ORMXX_NARGS_(...) __ORMXX_NARGS__(__VA_ARGS__)
#define __ORMXX_NARGS__(...) __ORMXX_NARGS___(__VA_ARGS__)
#define __ORMXX_NARGS___(...) __ORMXX_NARGS_____(__VA_ARGS__, __ORMXX_ARG_RSET_N_)
#define __ORMXX_NARGS_____(...) __ORMXX_ARG_N_(__VA_ARGS__)
#define __ORMXX_ARG_N_(_1,   \
                       _2,   \
                       _3,   \
                       _4,   \
                       _5,   \
                       _6,   \
                       _7,   \
                       _8,   \
                       _9,   \
                       _10,  \
                       _11,  \
                       _12,  \
                       _13,  \
                       _14,  \
                       _15,  \
                       _16,  \
                       _17,  \
                       _18,  \
                       _19,  \
                       _20,  \
                       _21,  \
                       _22,  \
                       _23,  \
                       _24,  \
                       _25,  \
                       _26,  \
                       _27,  \
                       _28,  \
                       _29,  \
                       _30,  \
                       _31,  \
                       _32,  \
                       _33,  \
                       _34,  \
                       _35,  \
                       _36,  \
                       _37,  \
                       _38,  \
                       _39,  \
                       _40,  \
                       _41,  \
                       _42,  \
                       _43,  \
                       _44,  \
                       _45,  \
                       _46,  \
                       _47,  \
                       _48,  \
                       _49,  \
                       _50,  \
                       _51,  \
                       _52,  \
                       _53,  \
                       _54,  \
                       _55,  \
                       _56,  \
                       _57,  \
                       _58,  \
                       _59,  \
                       _60,  \
                       _61,  \
                       _62,  \
                       _63,  \
                       _64,  \
                       _65,  \
                       _66,  \
                       _67,  \
                       _68,  \
                       _69,  \
                       _70,  \
                       _71,  \
                       _72,  \
                       _73,  \
                       _74,  \
                       _75,  \
                       _76,  \
                       _77,  \
                       _78,  \
                       _79,  \
                       _80,  \
                       _81,  \
                       _82,  \
                       _83,  \
                       _84,  \
                       _85,  \
                       _86,  \
                       _87,  \
                       _88,  \
                       _89,  \
                       _90,  \
                       _91,  \
                       _92,  \
                       _93,  \
                       _94,  \
                       _95,  \
                       _96,  \
                       _97,  \
                       _98,  \
                       _99,  \
                       _100, \
                       _101, \
                       _102, \
                       _103, \
                       _104, \
                       _105, \
                       _106, \
                       _107, \
                       _108, \
                       _109, \
                       _110, \
                       _111, \
                       _112, \
                       _113, \
                       _114, \
                       _115, \
                       _116, \
                       _117, \
                       _118, \
                       _119, \
                       _120, \
                       _121, \
                       _122, \
                       _123, \
                       _124, \
                       _125, \
                       _126, \
                       _127, \
                       _128, \
                       _129, \
                       _130, \
                       _131, \
                       _132, \
                       _133, \
                       _134, \
                       _135, \
                       _136, \
                       _137, \
                       _138, \
                       _139, \
                       _140, \
                       _141, \
                       _142, \
                       _143, \
                       _144, \
                       _145, \
                       _146, \
                       _147, \
                       _148, \
                       _149, \
                       _150, \
                       _151, \
                       _152, \
                       _153, \
                       _154, \
                       _155, \
                       _156, \
                       _157, \
                       _158, \
                       _159, \
                       _160, \
                       _161, \
                       _162, \
                       _163, \
                       _164, \
                       _165, \
                       _166, \
                       _167, \
                       _168, \
                       _169, \
                       _170, \
                       _171, \
                       _172, \
                       _173, \
                       _174, \
                       _175, \
                       _176, \
                       _177, \
                       _178, \
                       _179, \
                       _180, \
                       _181, \
                       _182, \
                       _183, \
                       _184, \
                       _185, \
                       _186, \
                       _187, \
                       _188, \
                       _189, \
                       _190, \
                       _191, \
                       _192, \
                       _193, \
                       _194, \
                       _195, \
                       _196, \
                       _197, \
                       _198, \
                       _199, \
                       _200, \
                       _201, \
                       _202, \
                       _203, \
                       _204, \
                       _205, \
                       _206, \
                       _207, \
                       _208, \
                       _209, \
                       _210, \
                       _211, \
                       _212, \
                       _213, \
                       _214, \
                       _215, \
                       _216, \
                       _217, \
                       _218, \
                       _219, \
                       _220, \
                       _221, \
                       _222, \
                       _223, \
                       _224, \
                       _225, \
                       _226, \
                       _227, \
                       _228, \
                       _229, \
                       _230, \
                       _231, \
                       _232, \
                       _233, \
                       _234, \
                       _235, \
                       _236, \
                       _237, \
                       _238, \
                       _239, \
                       _240, \
                       _241, \
                       _242, \
                       _243, \
                       _244, \
                       _245, \
                       _246, \
                       _247, \
                       _248, \
                       _249, \
                       _250, \
                       _251, \
                       _252, \
                       _253, \
                       _254, \
                       _255, \
                       _256, \
                       N,    \
                       ...)  \
    N

#define __ORMXX_ARG_RSET_N_                                                                                            \
    256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 235, 234, \
            233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213,   \
            212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192,   \
            191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171,   \
            170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150,   \
            149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129,   \
            128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108,   \
            107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84,    \
            83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58,    \
            57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,    \
            31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4,  \
            3, 2, 1, 0

#define __ORMXX_EXPEND_FUNC_1(func, a) func(a)
#define __ORMXX_EXPEND_FUNC_2(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_1(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_3(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_2(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_4(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_3(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_5(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_4(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_6(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_5(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_7(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_6(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_8(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_7(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_9(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_8(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_10(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_9(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_11(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_10(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_12(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_11(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_13(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_12(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_14(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_13(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_15(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_14(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_16(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_15(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_17(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_16(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_18(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_17(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_19(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_18(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_20(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_19(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_21(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_20(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_22(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_21(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_23(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_22(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_24(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_23(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_25(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_24(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_26(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_25(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_27(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_26(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_28(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_27(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_29(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_28(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_30(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_29(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_31(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_30(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_32(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_31(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_33(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_32(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_34(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_33(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_35(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_34(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_36(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_35(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_37(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_36(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_38(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_37(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_39(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_38(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_40(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_39(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_41(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_40(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_42(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_41(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_43(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_42(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_44(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_43(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_45(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_44(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_46(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_45(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_47(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_46(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_48(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_47(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_49(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_48(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_50(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_49(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_51(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_50(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_52(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_51(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_53(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_52(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_54(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_53(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_55(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_54(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_56(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_55(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_57(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_56(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_58(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_57(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_59(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_58(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_60(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_59(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_61(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_60(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_62(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_61(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_63(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_62(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_64(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_63(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_65(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_64(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_66(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_65(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_67(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_66(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_68(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_67(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_69(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_68(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_70(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_69(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_71(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_70(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_72(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_71(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_73(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_72(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_74(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_73(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_75(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_74(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_76(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_75(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_77(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_76(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_78(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_77(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_79(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_78(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_80(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_79(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_81(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_80(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_82(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_81(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_83(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_82(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_84(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_83(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_85(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_84(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_86(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_85(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_87(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_86(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_88(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_87(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_89(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_88(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_90(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_89(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_91(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_90(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_92(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_91(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_93(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_92(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_94(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_93(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_95(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_94(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_96(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_95(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_97(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_96(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_98(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_97(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_99(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_98(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_100(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_99(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_101(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_100(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_102(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_101(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_103(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_102(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_104(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_103(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_105(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_104(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_106(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_105(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_107(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_106(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_108(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_107(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_109(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_108(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_110(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_109(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_111(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_110(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_112(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_111(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_113(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_112(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_114(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_113(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_115(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_114(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_116(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_115(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_117(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_116(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_118(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_117(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_119(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_118(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_120(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_119(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_121(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_120(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_122(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_121(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_123(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_122(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_124(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_123(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_125(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_124(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_126(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_125(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_127(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_126(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_128(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_127(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_129(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_128(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_130(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_129(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_131(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_130(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_132(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_131(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_133(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_132(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_134(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_133(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_135(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_134(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_136(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_135(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_137(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_136(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_138(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_137(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_139(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_138(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_140(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_139(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_141(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_140(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_142(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_141(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_143(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_142(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_144(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_143(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_145(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_144(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_146(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_145(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_147(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_146(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_148(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_147(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_149(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_148(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_150(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_149(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_151(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_150(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_152(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_151(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_153(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_152(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_154(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_153(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_155(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_154(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_156(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_155(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_157(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_156(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_158(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_157(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_159(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_158(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_160(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_159(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_161(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_160(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_162(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_161(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_163(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_162(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_164(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_163(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_165(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_164(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_166(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_165(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_167(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_166(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_168(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_167(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_169(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_168(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_170(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_169(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_171(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_170(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_172(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_171(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_173(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_172(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_174(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_173(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_175(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_174(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_176(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_175(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_177(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_176(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_178(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_177(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_179(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_178(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_180(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_179(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_181(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_180(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_182(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_181(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_183(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_182(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_184(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_183(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_185(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_184(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_186(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_185(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_187(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_186(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_188(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_187(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_189(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_188(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_190(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_189(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_191(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_190(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_192(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_191(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_193(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_192(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_194(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_193(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_195(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_194(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_196(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_195(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_197(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_196(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_198(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_197(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_199(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_198(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_200(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_199(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_201(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_200(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_202(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_201(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_203(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_202(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_204(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_203(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_205(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_204(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_206(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_205(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_207(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_206(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_208(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_207(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_209(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_208(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_210(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_209(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_211(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_210(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_212(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_211(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_213(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_212(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_214(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_213(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_215(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_214(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_216(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_215(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_217(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_216(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_218(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_217(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_219(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_218(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_220(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_219(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_221(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_220(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_222(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_221(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_223(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_222(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_224(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_223(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_225(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_224(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_226(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_225(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_227(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_226(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_228(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_227(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_229(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_228(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_230(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_229(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_231(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_230(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_232(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_231(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_233(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_232(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_234(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_233(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_235(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_234(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_236(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_235(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_237(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_236(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_238(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_237(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_239(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_238(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_240(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_239(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_241(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_240(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_242(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_241(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_243(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_242(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_244(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_243(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_245(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_244(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_246(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_245(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_247(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_246(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_248(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_247(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_249(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_248(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_250(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_249(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_251(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_250(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_252(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_251(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_253(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_252(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_254(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_253(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_255(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_254(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_256(func, a, ...) func(a) __ORMXX_EXPEND_FUNC_255(func, __VA_ARGS__)

#define __ORMXX_EXPEND_FUNC___(func, NARGS, ...) __ORMXX_EXPEND_FUNC_##NARGS(func, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC__(func, NARGS, ...) __ORMXX_EXPEND_FUNC___(func, NARGS, __VA_ARGS__)
#define __ORMXX_EXPEND_FUNC_(func, ...) __ORMXX_EXPEND_FUNC__(func, __ORMXX_NARGS_(__VA_ARGS__), __VA_ARGS__)

#endif  // ORMXX_INTERNAL_MACROS_UTILITY_H
