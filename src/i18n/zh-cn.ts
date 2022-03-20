import { Language } from "element-plus/lib/locale";
import lang from "element-plus/lib/locale/lang/zh-cn";

const exp: Language = {
  ...lang,
  el: {
    ...lang.el,
    perfcat: {
      about: "关于",
      actions: "操作",
      advanced: "高级",
      application: "应用",
      backend: "后端",
      device: "设备",
      export: "导出",
      performance: "性能",
      record: "录制",
      submit: "提交",
      surface: "图形窗口",
      targetFps: "目标 FPS",
    },
  },
};

export default exp;
