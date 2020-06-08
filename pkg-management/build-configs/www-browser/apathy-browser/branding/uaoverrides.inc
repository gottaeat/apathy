#define GUAO_PREF general.useragent.override

// act as firefox 52-esr by default
pref("@GUAO_PREF@",             "Mozilla/5.0 (X11; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0");

// site specific overrides
pref("@GUAO_PREF@.pixiv.net",   "Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");
pref("@GUAO_PREF@.deezer.com",  "Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");
