import { createApp } from "vue";
import ElementPlus from "element-plus";
import { createPinia } from "pinia";
import "element-plus/dist/index.css";
import App from "./App.vue";
import router from "./router";

createApp(App).use(router).use(createPinia()).use(ElementPlus).mount("#app");
