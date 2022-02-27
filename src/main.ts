import { createApp } from "vue";
import ElementPlus from "element-plus";
import { createPinia } from "pinia";
import { createI18n } from "vue-i18n";
import "element-plus/dist/index.css";
import App from "./App.vue";
import router from "./router";

import messages from "@/i18n";

const i18n = createI18n({
  legacy: false,
  locale: "en",
  fallbackLocale: "en",
  messages,
});

createApp(App)
  .use(router)
  .use(i18n)
  .use(createPinia())
  .use(ElementPlus)
  .mount("#app");
