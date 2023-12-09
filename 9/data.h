#ifndef DATA_H
#define DATA_H

const char *test_input[] = {
	"0 3 6 9 12 15",
	"1 3 6 10 15 21",
	"10 13 16 21 30 45"
};

const char *input[] = {
	"26 35 42 63 136 327 729 1457 2648 4480 7229 11394 17952 28881 48234 84291 153739 289701 557511 1087187 2143197",
	"-6 -7 -7 -6 -4 -1 3 8 14 21 29 38 48 59 71 84 98 113 129 146 164",
	"10 21 39 71 124 205 321 479 686 949 1275 1671 2144 2701 3349 4095 4946 5909 6991 8199 9540",
	"17 36 64 110 196 368 721 1447 2915 5792 11214 21016 38030 66460 112343 184105 293221 454988 689420 1022274 1486216",
	"14 33 64 116 204 363 671 1289 2540 5066 10129 20190 40081 79524 158734 320937 659964 1379861 2920964 6221222 13247612",
	"10 17 41 95 198 375 657 1081 1690 2533 3665 5147 7046 9435 12393 16005 20362 25561 31705 38903 47270",
	"14 29 64 124 216 352 565 958 1808 3743 8000 16767 33646 64419 118683 213748 383770 699853 1311392 2526026 4956236",
	"19 30 47 86 178 369 720 1307 2221 3568 5469 8060 11492 15931 21558 28569 37175 47602 60091 74898 92294",
	"1 13 30 66 156 361 782 1589 3082 5828 10975 20973 41216 83707 175021 373168 802624 1726245 3691904 7830015 16453595",
	"7 6 12 33 86 197 399 741 1345 2591 5587 13218 32302 77760 180292 399922 849043 1730420 3398238 6454079 11895222",
	"20 40 66 104 168 288 538 1089 2290 4780 9636 18566 34162 60236 102272 168039 268424 418560 639342 959444 1417972",
	"4 1 8 49 171 457 1047 2169 4174 7572 13095 21883 36015 59804 102558 183893 343184 655371 1256114 2380229 4418451",
	"11 21 44 94 190 354 607 963 1421 1955 2502 2948 3112 2728 1425 -1295 -6081 -13759 -25360 -42150 -65662",
	"-5 2 24 67 140 257 432 667 941 1223 1565 2410 5431 15611 46111 129246 340658 851773 2042419 4740096 10722177",
	"30 42 54 78 144 309 666 1353 2562 4548 7638 12240 18852 28071 40602 57267 79014 106926 142230 186306 240696",
	"4 5 6 4 -2 -6 16 144 614 2030 5756 14577 33738 72479 146164 279025 507368 882763 1474194 2367290 3657486",
	"15 39 71 119 214 419 847 1704 3385 6680 13205 26287 52768 106695 216910 442638 905099 1850193 3769279 7624639 15257058",
	"3 12 37 84 157 259 396 590 917 1601 3217 7084 15961 35198 74558 151062 293511 549970 1000717 1781348 3124429",
	"30 52 78 111 156 226 363 678 1414 3032 6311 12445 23129 40681 68393 111605 180538 296816 506992 908439 1695878",
	"13 11 22 61 142 275 477 809 1456 2892 6241 14089 32266 73589 165430 364651 786707 1661933 3443480 7011621 14053570",
	"12 39 91 193 395 786 1514 2811 5024 8670 14583 24331 41297 73223 137768 274043 565775 1186884 2489910 5175384 10611406",
	"17 30 44 61 96 187 413 924 1999 4173 8512 17166 34394 68332 133865 257067 481789 879104 1560460 2695547 4536052",
	"4 11 19 37 82 184 404 887 1995 4606 10740 24810 56050 123161 263200 548769 1121742 2260137 4510825 8950315 17687738",
	"7 27 59 103 159 227 307 399 503 619 747 887 1039 1203 1379 1567 1767 1979 2203 2439 2687",
	"24 33 35 39 72 183 445 955 1832 3213 5247 8087 11880 16755 22809 30091 38584 48185 58683 69735 80840",
	"14 25 44 81 158 317 646 1349 2901 6354 13911 29992 63242 130402 263910 526903 1042536 2050026 4008556 7783136 14964330",
	"14 36 82 176 361 717 1400 2716 5251 10085 19128 35643 65091 116595 205685 359815 630008 1116030 2020826 3766194 7231721",
	"7 22 46 81 131 199 287 419 728 1675 4501 12052 30162 69830 150484 304688 584717 1071500 1886512 3207283 5287285",
	"0 13 51 141 338 752 1597 3285 6611 13106 25672 49656 94583 176907 324514 584721 1040090 1842598 3291085 6008902 11347440",
	"26 54 99 165 256 376 529 719 950 1226 1551 1929 2364 2860 3421 4051 4754 5534 6395 7341 8376",
	"5 8 30 96 252 576 1189 2266 4047 6848 11072 17220 25902 37848 53919 75118 102601 137688 181874 236840 304464",
	"18 30 38 43 47 60 122 355 1072 2987 7605 17945 39891 84713 173697 346423 675094 1288516 2410936 4423047 7955159",
	"15 33 70 148 318 690 1491 3159 6476 12736 23937 42981 73861 121799 193252 295586 435973 618611 838592 1069506 1239992",
	"12 25 44 83 177 411 974 2247 4940 10314 20568 39558 74189 137162 252394 465548 863972 1613295 3022404 5655077 10515841",
	"17 23 28 32 35 37 38 38 37 35 32 28 23 17 10 2 -7 -17 -28 -40 -53",
	"20 27 34 41 48 55 62 69 76 83 90 97 104 111 118 125 132 139 146 153 160",
	"14 28 63 140 289 549 968 1603 2520 3794 5509 7758 10643 14275 18774 24269 30898 38808 48155 59104 71829",
	"11 13 25 60 131 258 496 1006 2196 4970 11163 24360 51603 107183 221143 457846 954845 2000571 4182761 8660420 17643527",
	"1 12 46 110 209 345 517 731 1033 1584 2809 5682 12277 26869 58216 124413 263297 554524 1165328 2442470 5090777",
	"1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21",
	"10 19 28 36 37 21 -18 -55 28 563 2326 6990 18036 42542 94505 200604 409561 806558 1534779 2827723 5059814",
	"8 31 67 121 207 352 604 1053 1886 3529 6995 14671 31953 70390 153340 325587 668932 1326467 2539083 4698765 8424403",
	"15 39 77 136 230 387 668 1209 2294 4459 8612 16133 28911 49357 80812 129945 215765 396795 842423 2002558 4981136",
	"8 4 -7 -26 -38 11 245 898 2373 5351 11022 21596 41452 79760 156506 316211 658402 1402950 3024695 6519782 13912298",
	"24 49 97 177 299 483 776 1277 2170 3765 6547 11233 18837 30743 48786 75341 113420 166777 240021 338737 469615",
	"-5 -4 3 23 81 241 651 1635 3864 8647 18392 37296 72332 134610 241198 417498 700281 1141494 1812961 2812109 4268859",
	"13 24 37 60 120 280 664 1498 3179 6388 12267 22684 40614 70668 119806 198274 320809 508160 788977 1202124 1799476",
	"-8 1 27 85 201 414 780 1377 2310 3715 5761 8649 12607 17880 24714 33333 43908 56517 71095 87373 104805",
	"4 10 26 58 117 232 475 1002 2120 4392 8797 16987 31757 58013 104866 190153 350020 658890 1270556 2501848 5000829",
	"5 23 60 133 271 521 957 1692 2895 4833 8000 13465 23669 44023 85797 170932 339537 660931 1249132 2283653 4036307",
	"-6 0 21 76 210 510 1137 2387 4793 9279 17376 31509 55363 94335 156078 251142 393716 602474 901527 1321482 1900608",
	"7 26 69 161 350 715 1369 2453 4123 6547 9953 14802 22202 34730 57889 102496 188375 349816 643357 1158551 2032494",
	"8 24 59 124 241 451 822 1457 2502 4154 6669 10370 15655 23005 32992 46287 63668 86028 114383 149880 193805",
	"14 25 29 28 36 87 252 670 1597 3476 7030 13379 24181 41796 69471 111543 173656 262987 388475 561046 793826",
	"13 30 69 137 253 466 879 1679 3173 5830 10329 17613 28949 45994 70867 106227 155357 222254 311725 429489 582285",
	"19 26 27 20 5 -1 63 341 1111 2848 6299 12570 23225 40397 66911 106419 163547 244054 355003 504944 704109",
	"11 27 63 139 287 567 1091 2060 3840 7143 13442 25839 50726 100735 199668 390336 746521 1390611 2518849 4436587 7606449",
	"8 16 24 32 40 48 56 64 72 80 88 96 104 112 120 128 136 144 152 160 168",
	"24 40 58 74 78 56 3 -38 120 1023 4036 12295 32615 79211 180836 394437 831547 1710256 3459759 6934492 13857367",
	"21 45 80 133 233 459 998 2243 4936 10358 20569 38708 69378 119166 197385 317176 497175 764035 1156198 1729439 2564855",
	"-6 4 24 55 102 175 297 527 1012 2103 4618 10422 23632 52956 115951 246348 506054 1004014 1924812 3570721 6421890",
	"5 14 25 41 81 201 538 1392 3361 7544 15827 31267 58589 104811 180012 298258 478701 746866 1136141 1689485 2461369",
	"8 15 20 23 24 23 20 15 8 -1 -12 -25 -40 -57 -76 -97 -120 -145 -172 -201 -232",
	"13 20 30 48 76 118 195 384 904 2280 5634 13208 29381 62826 131291 272156 564999 1177756 2456894 5095984 10438354",
	"27 53 96 159 255 426 783 1588 3411 7409 15783 32472 64154 121681 222249 393008 677615 1148649 1931134 3246025 5487861",
	"27 51 87 147 252 443 811 1568 3204 6815 14760 31931 68124 142316 290137 576563 1116981 2111495 3899953 7049103 12489112",
	"15 38 65 106 199 432 972 2103 4287 8284 15397 27949 50166 89761 160728 288225 517106 927093 1660904 2979519 5376696",
	"0 6 31 85 194 412 837 1643 3145 5918 10995 20188 36667 66241 120629 226030 444760 927057 2029015 4569804 10373398",
	"19 26 33 40 47 54 61 68 75 82 89 96 103 110 117 124 131 138 145 152 159",
	"10 25 53 115 238 467 889 1678 3189 6155 12074 23913 47303 92453 177072 330656 600572 1060453 1821507 3047439 4973788",
	"-5 6 42 116 241 430 696 1052 1511 2086 2790 3636 4637 5806 7156 8700 10451 12422 14626 17076 19785",
	"13 40 92 178 320 570 1025 1832 3175 5243 8195 12175 17526 25612 41304 79628 181985 452774 1136694 2772588 6484284",
	"19 23 26 28 29 29 28 26 23 19 14 8 1 -7 -16 -26 -37 -49 -62 -76 -91",
	"17 28 51 84 122 162 210 294 504 1118 2937 8043 21309 53122 123918 271257 560267 1098336 2054903 3687062 6371412",
	"20 28 35 44 76 178 438 1031 2334 5162 11191 23648 48362 95284 180598 329559 580208 988128 1632419 2623084 4110032",
	"5 20 47 86 137 200 275 362 461 572 695 830 977 1136 1307 1490 1685 1892 2111 2342 2585",
	"26 38 56 87 148 291 641 1446 3149 6514 12872 24600 46007 84877 155011 280219 500340 880014 1521096 2579789 4289782",
	"10 18 29 45 77 160 369 829 1716 3258 5769 9790 16486 28609 52706 104067 217586 470910 1031969 2252631 4845759",
	"-1 10 31 62 103 154 215 286 367 458 559 670 791 922 1063 1214 1375 1546 1727 1918 2119",
	"8 12 20 49 121 260 489 827 1286 1868 2562 3341 4159 4948 5615 6039 6068 5516 4160 1737 -2059",
	"0 -4 -4 15 71 192 450 1034 2366 5263 11181 22696 44675 87230 172812 352167 738124 1573554 3362222 7111453 14767575",
	"19 37 73 130 204 280 340 404 636 1566 4512 12341 30798 70777 152136 310006 605061 1139971 2085359 3720200 6494028",
	"2 5 28 82 185 374 731 1434 2842 5621 10916 20572 37405 65522 110687 180728 285978 439741 658772 963758 1379785",
	"27 49 80 126 197 310 504 885 1731 3696 8158 17757 37162 74103 140767 255956 449312 771177 1316772 2284435 4111174",
	"-9 -14 -19 -24 -29 -34 -39 -44 -49 -54 -59 -64 -69 -74 -79 -84 -89 -94 -99 -104 -109",
	"6 15 27 46 76 121 185 272 386 531 711 930 1192 1501 1861 2276 2750 3287 3891 4566 5316",
	"10 9 8 12 42 163 524 1407 3284 6886 13297 24100 41622 69352 112641 179837 284062 445903 697366 1087532 1690458",
	"0 9 24 44 68 105 193 433 1055 2544 5865 12837 26717 53066 100980 184780 326266 557651 925302 1494426 2354850",
	"10 12 10 4 -6 -20 -38 -60 -86 -116 -150 -188 -230 -276 -326 -380 -438 -500 -566 -636 -710",
	"8 20 45 89 168 331 691 1470 3073 6209 12068 22530 40306 68775 111098 168065 234382 294482 323003 304787 309948",
	"24 49 89 155 273 496 928 1779 3491 7003 14260 29127 58966 117310 228381 434731 810146 1481285 2663507 4719187 8250799",
	"19 33 62 128 264 514 933 1587 2553 3919 5784 8258 11462 15528 20599 26829 34383 43437 54178 66804 81524",
	"8 22 53 122 270 578 1193 2355 4413 7810 13019 20456 30543 44436 66599 111605 219725 490109 1149268 2691985 6174015",
	"26 50 82 123 185 303 566 1175 2531 5351 10805 20662 37428 64454 105987 167132 253688 371816 527492 725693 969259",
	"14 35 80 158 278 449 680 980 1358 1823 2384 3050 3830 4733 5768 6944 8270 9755 11408 13238 15254",
	"11 11 15 23 35 51 71 95 123 155 191 231 275 323 375 431 491 555 623 695 771",
	"6 16 24 35 58 96 141 187 289 723 2341 7266 20135 50173 114468 242916 485416 922018 1676862 2936893 4976496",
	"11 20 49 110 227 453 898 1768 3424 6485 12017 21877 39339 70262 125339 224493 405397 739562 1361669 2521064 4668871",
	"20 37 80 158 285 497 885 1648 3160 6035 11176 19837 33870 56674 96069 171621 331201 685379 1474871 3198556 6854496",
	"4 6 20 55 138 338 805 1841 4037 8544 17608 35600 70923 139390 269951 514014 960066 1755866 3141164 5494709 9400256",
	"8 13 34 90 208 430 841 1627 3186 6356 12910 26629 55545 116404 243087 501667 1015960 2008922 3867653 7245316 13228060",
	"3 16 37 69 124 232 465 1001 2269 5236 11921 26249 55390 111764 215933 400645 716343 1238504 2077229 3389565 5395104",
	"24 45 85 166 322 598 1063 1847 3218 5732 10517 19791 37764 72135 136467 253806 462004 821311 1424917 2413252 3992990",
	"7 24 56 109 189 302 454 651 899 1204 1572 2009 2521 3114 3794 4567 5439 6416 7504 8709 10037",
	"6 6 15 43 91 159 276 558 1303 3152 7405 16728 36804 80099 174024 377639 814012 1729858 3600691 7309097 14436681",
	"14 20 37 71 127 210 320 440 518 446 41 -965 -2917 -6200 -11160 -17968 -26410 -35584 -43483 -46441 -38417",
	"12 17 16 12 25 120 460 1409 3724 8883 19602 40622 79965 151215 278256 505768 922388 1709889 3242580 6278524 12310953",
	"9 9 10 7 -6 -23 -1 179 775 2311 5872 13776 30987 67865 145228 303374 617945 1227749 2383562 4533485 8470988",
	"9 11 14 19 43 131 362 843 1689 2997 4835 7291 10709 16508 29705 65926 169073 452107 1184316 2966327 7062159",
	"4 19 44 77 112 138 134 62 -137 -530 -1130 -1722 -1448 2152 15406 53958 155715 410547 1025294 2459060 5690975",
	"17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49 51 53 55 57",
	"28 38 41 31 8 1 117 624 2070 5435 12324 25277 48475 89589 164469 308195 599485 1212145 2520288 5309464 11194667",
	"1 4 2 -6 -13 14 174 709 2139 5482 12592 26654 52881 99464 178832 309285 517069 838968 1325494 2044762 3087143",
	"-1 15 45 97 186 335 592 1078 2095 4347 9373 20396 44024 93710 196770 408372 838760 1704980 3427198 6805400 13340371",
	"24 49 98 179 297 454 662 979 1576 2850 5634 11665 24741 53576 118484 266044 599328 1336819 2921754 6216539 12835689",
	"21 43 91 177 313 527 903 1662 3307 6861 14233 28753 55923 104437 187529 324714 543993 884599 1400367 2163817 3271045",
	"10 20 48 110 232 449 817 1461 2691 5227 10583 21669 43679 85342 160622 290962 508176 858102 1405138 2237792 3475386",
	"11 35 84 169 305 523 890 1537 2706 4864 9012 17463 35603 75523 162993 350202 738357 1517321 3035288 5922273 11310317",
	"5 16 36 79 164 317 575 988 1620 2577 4149 7249 14465 32206 74610 170076 371463 771142 1522162 2866763 5173298",
	"23 47 91 180 355 676 1237 2209 3932 7082 12944 23827 43662 78829 139264 239902 402517 658025 1049321 1634726 2492125",
	"15 23 27 34 62 157 432 1136 2766 6255 13310 27042 53131 101922 192141 357660 660775 1220785 2279451 4353200 8580138",
	"22 35 50 71 109 182 315 540 896 1429 2192 3245 4655 6496 8849 11802 15450 19895 25246 31619 39137",
	"19 46 99 184 301 445 609 789 991 1240 1591 2142 3049 4543 6949 10707 16395 24754 36715 53428 76293",
	"16 35 78 161 304 532 886 1455 2451 4374 8370 17012 36007 77877 169678 368610 792378 1676029 3474614 7042651 13938682",
	"11 21 37 74 161 344 684 1257 2179 3705 6498 12267 25210 55211 124765 283528 637855 1408801 3042715 6416976 13214939",
	"28 50 82 125 194 336 661 1391 2939 6053 12112 23759 46217 89871 175017 340071 654974 1241980 2306406 4180161 7380828",
	"16 33 52 76 116 194 346 625 1104 1879 3072 4834 7348 10832 15542 21775 29872 40221 53260 69480 89428",
	"13 19 43 102 215 403 689 1098 1657 2395 3343 4534 6003 7787 9925 12458 15429 18883 22867 27430 32623",
	"23 28 25 23 41 115 318 793 1799 3774 7427 13883 24921 43365 73712 123109 202823 330384 532621 849855 1341561",
	"8 13 31 81 190 392 739 1348 2529 5075 10857 23969 52827 113862 237783 479848 936198 1769113 3245075 5790809 10074060",
	"5 -1 -3 1 24 102 309 788 1831 4088 9089 20476 46745 107008 242462 538106 1162045 2433793 4938737 9713831 18540218",
	"23 36 67 128 238 432 765 1304 2096 3100 4082 4498 3433 -276 -7530 -17782 -26795 -22876 18957 145468 436960",
	"19 19 10 -13 -55 -121 -216 -345 -513 -725 -986 -1301 -1675 -2113 -2620 -3201 -3861 -4605 -5438 -6365 -7391",
	"13 22 35 63 127 273 594 1257 2533 4828 8713 14951 24519 38623 58704 86433 123693 172546 235183 313855 410783",
	"15 29 62 138 301 623 1211 2210 3808 6273 10109 16538 28739 54658 112833 243745 531201 1142472 2405599 4965114 10110423",
	"22 31 40 45 47 68 173 508 1375 3376 7669 16390 33306 64775 121100 218375 380932 644509 1060270 1699819 2661361",
	"16 37 69 115 199 383 781 1560 2922 5084 8336 13405 22681 43553 96491 233174 574927 1390866 3252030 7329342 15962906",
	"25 37 46 52 55 55 52 46 37 25 10 -8 -29 -53 -80 -110 -143 -179 -218 -260 -305",
	"-2 -1 16 58 135 261 456 747 1168 1759 2564 3628 4993 6693 8748 11157 13890 16879 20008 23102 25915",
	"7 17 54 130 269 530 1052 2143 4445 9217 18788 37242 71407 132230 236630 409931 688987 1126121 1794010 2791658 4251609",
	"15 31 72 160 334 671 1314 2518 4741 8835 16445 30812 58307 111210 212522 404027 759535 1406459 2560962 4585380 8082232",
	"24 33 42 51 60 69 78 87 96 105 114 123 132 141 150 159 168 177 186 195 204",
	"-5 -7 8 61 189 455 970 1944 3787 7293 13979 26755 51348 99453 195748 393249 805935 1675617 3503846 7302341 15051147",
	"11 20 46 108 230 441 775 1271 1973 2930 4196 5830 7896 10463 13605 17401 21935 27296 33578 40880 49306",
	"11 12 23 66 175 396 787 1418 2371 3740 5631 8162 11463 15676 20955 27466 35387 44908 56231 69570 85151",
	"15 22 38 68 118 206 383 768 1612 3433 7323 15646 33567 72250 155262 330921 695341 1434220 2896652 5722340 11055780",
	"3 7 20 59 150 322 611 1085 1914 3548 7156 15669 36147 84904 198134 453125 1009261 2185081 4599544 9425143 18831724",
	"5 15 27 42 71 139 295 632 1326 2724 5557 11438 23947 50845 108404 229791 481678 998568 2056522 4234421 8765038",
	"30 44 56 72 112 216 447 889 1638 2784 4382 6410 8712 10924 12381 12003 8158 -1500 -20220 -52372 -103696",
	"16 22 30 43 71 138 296 646 1378 2880 6037 12959 28588 64067 143715 319587 702164 1525018 3279356 6987931 14747917",
	"5 -1 -10 -24 -33 3 180 683 1836 4211 8897 18122 36552 73767 148641 296637 581375 1112247 2070344 3745532 6588173",
	"-5 3 30 90 209 447 946 2018 4291 8943 18077 35324 66803 122611 219053 381840 650467 1083915 1767680 2821894 4409941",
	"1 -6 -22 -51 -92 -122 -67 239 1107 3058 6900 13817 25470 44110 72703 115067 176021 261546 378958 537093 746504",
	"19 35 71 138 255 454 787 1341 2267 3829 6479 10964 18471 30816 50683 81919 129891 201911 307735 460142 675599",
	"5 1 -4 -15 -36 -60 -48 122 773 2679 7552 18927 43690 94632 194650 383626 729701 1347765 2429692 4293397 7461472",
	"22 47 84 133 194 267 352 449 558 679 812 957 1114 1283 1464 1657 1862 2079 2308 2549 2802",
	"27 39 50 67 106 190 350 637 1153 2109 3918 7331 13624 24844 44122 76061 127207 206611 326490 502995 757094",
	"21 36 62 113 217 419 794 1493 2869 5767 12110 25974 55446 115785 234945 463719 895201 1702826 3214226 6051331 11387971",
	"-4 11 40 84 152 276 534 1089 2268 4728 9788 20048 40471 80195 155561 295458 551743 1021562 1897525 3580679 6928437",
	"-3 -5 -7 -9 -11 -13 -15 -17 -19 -21 -23 -25 -27 -29 -31 -33 -35 -37 -39 -41 -43",
	"21 43 73 123 229 467 976 1988 3865 7143 12583 21229 34473 54127 82502 122494 177677 252403 351909 482431 651325",
	"19 29 34 46 94 224 497 985 1765 2911 4484 6520 9016 11914 15083 18299 21223 23377 24118 22610 17794",
	"8 20 32 44 56 68 80 92 104 116 128 140 152 164 176 188 200 212 224 236 248",
	"13 9 14 36 82 168 347 777 1871 4603 11095 25687 56799 120029 243083 473279 888469 1612225 2833960 4834202 8014380",
	"25 52 95 155 233 330 447 585 745 928 1135 1367 1625 1910 2223 2565 2937 3340 3775 4243 4745",
	"3 -1 -2 20 104 313 751 1601 3198 6178 11813 22782 44894 90788 187635 392864 825918 1731880 3607877 7451423 15241457",
	"11 18 34 74 172 382 776 1446 2531 4313 7458 13519 25868 51283 102484 201989 387747 721100 1297730 2262360 3828100",
	"8 9 20 59 166 424 993 2158 4401 8543 16094 30140 57443 113004 229225 473103 976710 1988685 3957728 7663297 14414036",
	"8 17 43 97 193 355 637 1160 2170 4121 7787 14407 25867 44923 75469 122854 194252 299089 449531 661037 952981",
	"5 18 52 121 242 433 719 1158 1897 3263 5891 10909 20287 37707 70876 137305 277557 583511 1255976 2720254 5860036",
	"26 48 79 117 160 206 253 299 342 380 411 433 444 442 425 391 338 264 167 45 -104",
	"4 20 64 149 286 484 750 1089 1504 1996 2564 3205 3914 4684 5506 6369 7260 8164 9064 9941 10774",
	"5 3 -2 -7 4 66 232 572 1184 2228 3986 6935 11795 19479 30826 45940 62887 75417 69278 16573 -132522",
	"29 46 64 77 76 47 -27 -150 -260 -81 1250 6043 19894 55385 139172 325018 716889 1508424 3047842 5940189 11200546",
	"7 31 76 154 286 522 977 1884 3677 7145 13741 26179 49495 92794 172036 314672 568255 1018307 1827378 3319972 6160648",
	"19 43 90 171 309 555 1000 1776 3052 5057 8209 13520 23625 45116 93448 202656 443653 957187 2010888 4094557 8074321",
	"14 31 63 137 309 692 1505 3161 6436 12799 25035 48359 92299 173720 321469 583243 1035418 1796727 3046839 5051069 8192641",
	"-7 -9 1 45 169 453 1023 2063 3818 6573 10587 15954 22359 28711 32700 30500 17219 -10581 -47711 -63885 29897",
	"5 8 18 46 107 216 385 636 1070 2070 4761 11892 29330 68346 148806 303230 581419 1054940 1820164 2997730 4725213",
	"0 12 32 64 133 307 740 1752 3974 8606 17870 35802 69654 132452 247836 459451 849236 1572432 2922448 5446084 10138507",
	"15 22 48 120 277 570 1062 1828 2955 4542 6700 9552 13233 17890 23682 30780 39367 49638 61800 76072 92685",
	"-1 8 36 92 185 324 518 776 1107 1520 2024 2628 3341 4172 5130 6224 7463 8856 10412 12140 14049",
	"24 54 114 233 454 838 1483 2582 4571 8460 16502 33454 68859 141115 284789 564103 1098634 2113702 4040682 7716703 14777228",
	"20 25 26 22 13 13 87 421 1430 3916 9320 20183 41055 80282 153373 289016 539288 996203 1817478 3265284 5762801",
	"9 14 30 68 146 310 661 1381 2749 5136 8966 14628 22322 31820 42121 50977 54265 45178 13206 -57124 -187782",
	"15 29 57 109 202 360 614 1002 1569 2367 3455 4899 6772 9154 12132 15800 20259 25617 31989 39497 48270",
	"1 -3 -11 -24 -42 -62 -67 -1 281 1125 3361 9019 23021 56870 136134 314735 700845 1501645 3097193 6156590 11811100",
	"15 40 76 138 251 454 820 1509 2883 5740 11784 24555 51208 105772 214907 427910 834275 1595448 3004280 5598992 10382837",
	"9 21 53 124 274 582 1207 2466 4963 9783 18765 34868 62644 108832 183087 298858 474429 734137 1109781 1642236 2383286",
	"5 8 7 2 -3 0 23 82 197 392 695 1138 1757 2592 3687 5090 6853 9032 11687 14882 18685",
	"17 32 48 73 137 316 778 1868 4250 9118 18486 35601 65661 117400 207006 367840 673662 1291711 2598975 5427196 11561076",
	"2 8 10 15 40 116 298 695 1555 3470 7810 17562 38853 83592 173896 349294 678160 1275444 2329586 4142553 7188278",
	"10 19 34 65 132 270 540 1046 1958 3541 6190 10471 17168 27336 42360 64020 94562 136775 194074 270589 371260",
	"10 18 18 9 -7 -25 -37 -32 4 88 240 483 843 1349 2033 2930 4078 5518 7294 9453 12045",
	"12 28 55 106 203 370 630 1008 1533 2219 2990 3512 2955 -59 -6445 -12294 4101 115235 521500 1722951 4891122",
	"7 11 18 46 125 297 616 1148 1971 3175 4862 7146 10153 14021 18900 24952 32351 41283 51946 64550 79317",
	"-4 2 13 29 50 76 107 143 184 230 281 337 398 464 535 611 692 778 869 965 1066",
	"1 1 3 6 16 56 181 502 1224 2706 5573 10986 21362 42224 86628 185139 407435 908045 2021984 4462911 9729426",
	"18 33 64 121 214 363 613 1050 1822 3197 5745 10819 21640 45488 97833 209864 442106 909229 1825714 3590277 6941170",
	"5 18 44 95 192 363 652 1159 2143 4239 8878 19090 41095 87619 185057 389110 818618 1727421 3653857 7725842 16273119"
};

#endif
