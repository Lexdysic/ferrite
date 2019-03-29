
#include "Ferrite.h"
#include "Basics\Language.h"

struct FrequencyDef
{
    String::CodePoint codepoint;
    uint frequency[ELanguage::Max];
};

static const FrequencyDef s_frequency[] = {
     { 'a',    {  8167,  7636,  6516, 11525, 14634, 12117, 11745, 12920,  9383, 10503,  7486,  6025, 10110, 12217,  8421 } },
     { 'b',    {  1492,   901,  1886,  2215,  1043,   980,   927,  2844,  1535,  1740,  1584,  2000,  1043,   281,   822 } },
     { 'c',    {  2782,  3260,  2732,  4019,  3882,   776,  4501,  1463,  1486,  3895,  1242,   565,     0,   281,   740 } },
     { 'd',    {  4253,  3669,  5076,  5510,  4992,  3044,  3736,  5206,  4702,  3725,  5933,  5858,  1575,  1043,  3475 } },
     { 'e',    { 12702, 14715, 16396, 12681, 11570,  8995, 11792,  9912, 10149,  7352, 17324, 15453,  6418,  7968,  7562 } },
     { 'f',    {  2228,  1066,  1656,   692,  1023,  1037,  1153,   461,  2027,   143,   805,  2406,  3013,   194,    84 } },
     { 'g',    {  2015,   866,  3009,  1768,  1303,  1171,  1644,  1253,  2862,  1731,  3403,  4077,  4241,   392,    92 } },
     { 'h',    {  6094,   737,  4577,   703,   781,   384,   636,  1212,  2090,  1015,  2380,  1621,  1871,  1851,  1356 } },
     { 'i',    {  6996,  7529,  6550,  6247,  6186, 10012, 10143,  9600,  5817,  8328,  6499,  6000,  7578, 10817,  6073 } },
     { 'j',    {   153,   613,   268,   443,   397,  3501,    11,    34,   614,  1836,  1461,   730,  1144,  2042,  1433 } },
     { 'k',    {   772,    49,  1417,    11,    15,  4163,     9,  5683,  3140,  2753,  2248,  3395,  3314,  4973,  2894 } },
     { 'l',    {  6996,  5456,  3437,  4967,  2779,  6145,  6510,  5922,  5275,  2564,  3568,  5229,  4532,  5761,  3802 } },
     { 'm',    {  2406,  2968,  2534,  3157,  4738,  2994,  2512,  3752,  3471,  2515,  2213,  3237,  4041,  3202,  2446 } },
     { 'n',    {  6749,  7095,  9776,  6712,  4046,  7955,  6883,  7987,  8542,  6237, 10032,  7240,  7711,  8826,  6468 } },
     { 'o',    {  7507,  5598,  2594,  8683,  9735,  8779,  9832,  2976,  4482,  6667,  6063,  4636,  2166,  5614,  6695 } },
     { 'p',    {  1929,  2521,   670,  2510,  2523,  2755,  3056,   886,  1839,  2445,  1370,  1756,   789,  1842,  1906 } },
     { 'q',    {    95,  1362,    18,   877,  1204,     0,   505,     0,    20,     0,     9,     7,     0,    13,     1 } },
     { 'r',    {  5987,  6693,  7003,  6871,  6530,  5914,  6367,  7722,  8431,  5243,  6411,  8956,  8581,  2872,  4799 } },
     { 's',    {  6327,  7948,  7273,  7977,  6805,  6092,  4981,  3014,  6590,  5224,  5733,  5805,  5630,  7862,  5212 } },
     { 't',    {  9056,  7244,  6154,  4632,  4736,  5276,  5623,  3314,  7691,  2475,  6923,  6862,  4953,  8750,  5727 } },
     { 'u',    {  2758,  6311,  4166,  2927,  3634,  3183,  3011,  3235,  1919,  2062,  2192,  1979,  4562,  5008,  2160 } },
     { 'v',    {   978,  1838,   846,  1138,  1575,  1904,  2097,   959,  2415,    12,  1854,  2332,  2437,  2250,  5344 } },
     { 'w',    {  2360,    74,  1921,    17,    37,     0,    33,     0,   142,  5813,  1821,    69,     0,    94,    16 } },
     { 'x',    {   150,   427,    34,   215,   253,     0,     3,     0,   159,     4,    36,    28,    46,    31,    27 } },
     { 'y',    {  1974,   128,    39,  1008,     6,     0,    20,  3336,   708,  3206,    35,   698,   900,  1745,  1043 } },
     { 'z',    {    74,   326,  1134,   517,   470,   494,  1181,  1500,    70,  4852,  1374,    34,     0,    51,  1503 } },
     { 0x00E0, {     0,   486,     0,     0,    72,     0,   635,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00E2, {     0,    51,     0,     0,   562,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00E1, {     0,     0,     0,   502,   118,     0,     0,     0,     0,     0,     0,     0,  1799,     0,   867 } },
     { 0x00E5, {     0,     0,     0,     0,     0,     0,     0,     0,  1338,     0,     0,  1190,     0,     3,     0 } },
     { 0x00E4, {     0,     0,   447,     0,     0,     0,     0,     0,  1797,     0,     0,     0,     0,  3577,     0 } },
     { 0x00E3, {     0,     0,     0,     0,   733,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0105, {     0,     0,     0,     0,     0,     0,     0,     0,     0,   699,     0,     0,     0,     0,     0 } },
     { 0x00E6, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   872,   867,     0,     0 } },
     { 0x0153, {     0,    18,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00E7, {     0,    85,     0,     0,   530,     0,     0,  1156,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0109, {     0,     0,     0,     0,     0,   657,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0107, {     0,     0,     0,     0,     0,     0,     0,     0,     0,   743,     0,     0,     0,     0,     0 } },
     { 0x010D, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   462 } },
     { 0x010F, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,    15 } },
     { 0x00F0, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,  4393,     0,     0 } },
     { 0x00E8, {     0,   271,     0,     0,     0,     0,   263,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00E9, {     0,  1504,     0,   433,   337,     0,     0,     0,     0,     0,     0,     0,   647,     0,   633 } },
     { 0x00EA, {     0,   225,     0,     0,   450,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00EB, {     0,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0119, {     0,     0,     0,     0,     0,     0,     0,     0,     0,  1035,     0,     0,     0,     0,     0 } },
     { 0x011B, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,  1222 } },
     { 0x011D, {     0,     0,     0,     0,     0,   691,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x011F, {     0,     0,     0,     0,     0,     0,     0,  1125,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0125, {     0,     0,     0,     0,     0,    22,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00EE, {     0,    45,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00EC, {     0,     0,     0,     0,     0,     0,    30,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00ED, {     0,     0,     0,   725,   132,     0,     0,     0,     0,     0,     0,     0,  1570,     0,  1643 } },
     { 0x00EF, {     0,     5,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0131, {     0,     0,     0,     0,     0,     0,     0,  5114,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0135, {     0,     0,     0,     0,     0,    55,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0142, {     0,     0,     0,     0,     0,     0,     0,     0,     0,  2109,     0,     0,     0,     0,     0 } },
     { 0x00F1, {     0,     0,     0,   311,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0144, {     0,     0,     0,     0,     0,     0,     0,     0,     0,   362,     0,     0,     0,     0,     0 } },
     { 0x0148, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     7 } },
     { 0x00F2, {     0,     0,     0,     0,     0,     0,     2,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00F6, {     0,     0,   573,     0,     0,     0,     0,   777,  1305,     0,     0,     0,   777,   444,     0 } },
     { 0x00F4, {     0,    23,     0,     0,   635,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00F3, {     0,     0,     0,   827,   296,     0,     0,     0,     0,  1141,     0,     0,   994,     0,    24 } },
     { 0x00F8, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   939,     0,     0,     0 } },
     { 0x0159, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   380 } },
     { 0x015D, {     0,     0,     0,     0,     0,   385,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x015F, {     0,     0,     0,     0,     0,     0,     0,  1780,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x015B, {     0,     0,     0,     0,     0,     0,     0,     0,     0,   814,     0,     0,     0,     0,     0 } },
     { 0x0161, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   688 } },
     { 0x00DF, {     0,     0,   307,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x0165, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     6 } },
     { 0x00FE, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,  1455,     0,     0 } },
     { 0x00F9, {     0,    58,     0,     0,     0,     0,   166,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00FA, {     0,     0,     0,   168,   207,     0,     0,     0,     0,     0,     0,     0,   613,     0,    45 } },
     { 0x016D, {     0,     0,     0,     0,     0,   520,     0,     0,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x00FC, {     0,     0,   995,    12,    26,     0,     0,  1854,     0,     0,     0,     0,     0,     0,     0 } },
     { 0x016F, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   204 } },
     { 0x00FD, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   228,     0,   995 } },
     { 0x017A, {     0,     0,     0,     0,     0,     0,     0,     0,     0,    78,     0,     0,     0,     0,     0 } },
     { 0x017C, {     0,     0,     0,     0,     0,     0,     0,     0,     0,   706,     0,     0,     0,     0,     0 } },
     { 0x017E, {     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,   721 } },
};

uint s_totalSamples[ELanguage::Max];


AUTO_INIT_FUNC(FrequencyTest)
{
    for (auto def : s_frequency)
    {
        for (uint lang =  0; lang < uint(ELanguage::Max); ++lang)
        {
            s_totalSamples[lang] += def.frequency[lang];
        }
    }
}

static const wchar * s_stopwordsEnglish[] =
{
	L"a",
	L"about",
	L"above",
	L"after",
	L"again",
	L"against",
	L"all",
	L"am",
	L"an",
	L"and",
	L"any",
	L"are",
	L"aren't",
	L"as",
	L"at",
	L"be",
	L"because",
	L"been",
	L"before",
	L"being",
	L"below",
	L"between",
	L"both",
	L"but",
	L"by",
	L"can't",
	L"cannot",
	L"could",
	L"couldn't",
	L"did",
	L"didn't",
	L"do",
	L"does",
	L"doesn't",
	L"doing",
	L"don't",
	L"down",
	L"during",
	L"each",
	L"few",
	L"for",
	L"from",
	L"further",
	L"had",
	L"hadn't",
	L"has",
	L"hasn't",
	L"have",
	L"haven't",
	L"having",
	L"he",
	L"he'd",
	L"he'll",
	L"he's",
	L"her",
	L"here",
	L"here's",
	L"hers",
	L"herself",
	L"him",
	L"himself",
	L"his",
	L"how",
	L"how's",
	L"i",
	L"i'd",
	L"i'll",
	L"i'm",
	L"i've",
	L"if",
	L"in",
	L"into",
	L"is",
	L"isn't",
	L"it",
	L"it's",
	L"its",
	L"itself",
	L"let's",
	L"me",
	L"more",
	L"most",
	L"mustn't",
	L"my",
	L"myself",
	L"no",
	L"nor",
	L"not",
	L"of",
	L"off",
	L"on",
	L"once",
	L"only",
	L"or",
	L"other",
	L"ought",
	L"our",
	L"ours",
	L"ourselves",
	L"out",
	L"over",
	L"own",
	L"same",
	L"shan't",
	L"she",
	L"she'd",
	L"she'll",
	L"she's",
	L"should",
	L"shouldn't",
	L"so",
	L"some",
	L"such",
	L"than",
	L"that",
	L"that's",
	L"the",
	L"their",
	L"theirs",
	L"them",
	L"themselves",
	L"then",
	L"there",
	L"there's",
	L"these",
	L"they",
	L"they'd",
	L"they'll",
	L"they're",
	L"they've",
	L"this",
	L"those",
	L"through",
	L"to",
	L"too",
	L"under",
	L"until",
	L"up",
	L"very",
	L"was",
	L"wasn't",
	L"we",
	L"we'd",
	L"we'll",
	L"we're",
	L"we've",
	L"were",
	L"weren't",
	L"what",
	L"what's",
	L"when",
	L"when's",
	L"where",
	L"where's",
	L"which",
	L"while",
	L"who",
	L"who's",
	L"whom",
	L"why",
	L"why's",
	L"with",
	L"won't",
	L"would",
	L"wouldn't",
	L"you",
	L"you'd",
	L"you'll",
	L"you're",
	L"you've",
	L"your",
	L"yours",
	L"yourself",
	L"yourselves",
};

static const wchar * s_stopwordsFrench[] =
{
	L"alors",
	L"au",
	L"aucuns",
	L"aussi",
	L"autre",
	L"avant",
	L"avec",
	L"avoir",
	L"bon",
	L"car",
	L"ce",
	L"cela",
	L"ces",
	L"ceux",
	L"chaque",
	L"ci",
	L"comme",
	L"comment",
	L"dans",
	L"des",
	L"du",
	L"dedans",
	L"dehors",
	L"depuis",
	L"devrait",
	L"doit",
	L"donc",
	L"dos",
	L"début",
	L"elle",
	L"elles",
	L"en",
	L"encore",
	L"essai",
	L"est",
	L"et",
	L"eu",
	L"fait",
	L"faites",
	L"fois",
	L"font",
	L"hors",
	L"ici",
	L"il",
	L"ils",
	L"je",
	L"juste",
	L"la",
	L"le",
	L"les",
	L"leur",
	L"là",
	L"ma",
	L"maintenant",
	L"mais",
	L"mes",
	L"mine",
	L"moins",
	L"mon",
	L"mot",
	L"même",
	L"ni",
	L"nommés",
	L"notre",
	L"nous",
	L"ou",
	L"où",
	L"par",
	L"parce",
	L"pas",
	L"peut",
	L"peu",
	L"plupart",
	L"pour",
	L"pourquoi",
	L"quand",
	L"que",
	L"quel",
	L"quelle",
	L"quelles",
	L"quels",
	L"qui",
	L"sa",
	L"sans",
	L"ses",
	L"seulement",
	L"si",
	L"sien",
	L"son",
	L"sont",
	L"sous",
	L"soyez",
	L"sujet",
	L"sur",
	L"ta",
	L"tandis",
	L"tellement",
	L"tels",
	L"tes",
	L"ton",
	L"tous",
	L"tout",
	L"trop",
	L"très",
	L"tu",
	L"voient",
	L"vont",
	L"votre",
	L"vous",
	L"vu",
	L"ça",
	L"étaient",
	L"état",
	L"étions",
	L"été",
	L"être",
};

struct StopWordList
{
    const wchar ** list;
    uint           count;
};

static StopWordList s_stopwords[ELanguage::Max] = {
/*English*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*French*/		{ s_stopwordsFrench,  array_size(s_stopwordsFrench) },
/*German*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Spanish*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Portuguese*/	{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Esperanto*/	{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Italian*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Turkish*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Swedish*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Polish*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Dutch*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Danish*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Icelandic*/	{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Finnish*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
/*Czech*/		{ s_stopwordsEnglish, array_size(s_stopwordsEnglish) },
};

const FrequencyDef * FindFrequencyDef (String::CodePoint codepoint)
{
    for (auto & def : s_frequency)
    {
        if (codepoint != def.codepoint)
            continue;

        return &def;
    }
    return NULL;
}

const StopWordList * FindStopWordList (ELanguage lang)
{
    return s_stopwords + uint(lang);
}

//bool CharIsWord (String::CodePoint codepoint) {
//    auto cp = uint32(codepoint);
//    Math::IsInRange(cp, 'a', 'z');
//    Math::IsInRange(cp, 'A', 'Z');
//    Math::IsInRange(cp, '\'')
//}

ELanguage DetectLanguage (const wchar text[])
{
    uint frequency[ELanguage::Max] = {};
    for ( ; *text; text++)
    {
        auto ch = CharToLower(String::CodePoint(*text));
        auto frequencyDef = FindFrequencyDef(ch);
        if (!frequencyDef)
            continue;

        for (uint i = 0; i < uint(ELanguage::Max); i++)
            frequency[i] += frequencyDef->frequency[i];
    }

    float32 f[ELanguage::Max];
    for (uint lang = 0; lang < uint(ELanguage::Max); ++lang)
    {
        f[lang] = frequency[lang] * 100000 / float32(s_totalSamples[lang]);
    }
    

    auto best = std::max_element(f, f+array_size(f));
    if (best == f+array_size(f))
        ELanguage::Max;

    auto lang = ELanguage(best - f);
    return lang;
}

ELanguage DetectLanguage2 (const wchar text[])
{
    uint frequency[ELanguage::Max] = {};
    for ( ; *text; text++)
    {
        auto ch = CharToLower(String::CodePoint(*text));
        auto frequencyDef = FindFrequencyDef(ch);
        if (!frequencyDef)
            continue;

        for (uint i = 0; i < uint(ELanguage::Max); i++)
            frequency[i] += frequencyDef->frequency[i];
    }

    auto best = std::max_element(frequency, frequency+array_size(frequency));
    if (best == frequency+array_size(frequency))
        ELanguage::Max;

    auto lang = ELanguage(best - frequency);
    return lang;
}