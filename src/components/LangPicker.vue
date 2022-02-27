<template lang="pug">
.lang-picker
  el-form(label-width="40px", :model="form")
    el-form-item(label="🌐")
      el-select(placeholder="🌐", v-model="form.lang", @change="langChange")
        el-option(label="English" value="en")
        el-option(label="简体中文（中国）" value="zh-CN")
</template>

<script lang="ts">
export default {
  name: "LangPicker",
};
</script>

<script lang="ts" setup>
import { useLanguageStore } from "@/stores/language";
import { useI18n } from "vue-i18n";
import { reactive } from "vue";

const language = useLanguageStore();
const i18n = useI18n({ useScope: "global" });

/* eslint-disable @typescript-eslint/no-unused-vars */
const form = reactive({
  lang: language.lang,
});

const langChange = (val: string) => {
  language.setLang(val);
  i18n.locale.value = val;
};
/* eslint-enable */
</script>
