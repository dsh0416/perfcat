import { defineStore } from "pinia";

import en from "@/i18n/en";
import zhCn from "@/i18n/zh-cn";
import { Language } from "element-plus/lib/locale";

interface LanguageStore {
  lang: string;
  locale: Language;
}

export const useLanguageStore = defineStore("language", {
  state: () => {
    const ret: LanguageStore = { lang: "en", locale: en };
    return ret;
  },
  actions: {
    setLang(lang: string) {
      this.lang = lang;

      if (lang == "en") {
        this.locale = en;
      } else if (lang == "zh-CN") {
        this.locale = zhCn;
      } else {
        this.locale = en;
      }
    },
  },
});
