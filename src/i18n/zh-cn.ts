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
      cpuStats: "CPU 统计",
      device: "设备",
      export: "导出",
      memStats: "内存统计",
      performance: "性能",
      record: "录制",
      sipError: "检测到 SIP 打开，必须关闭 SIP 以获取 macOS 帧率。",
      submit: "提交",
      surface: "图形窗口",
      targetFps: "目标 FPS",
    },
  },
};

export default exp;
