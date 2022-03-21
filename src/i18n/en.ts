import { Language } from "element-plus/lib/locale";
import lang from "element-plus/lib/locale/lang/en";

const exp: Language = {
  ...lang,
  el: {
    ...lang.el,
    perfcat: {
      about: "About",
      actions: "Actions",
      advanced: "Advanced",
      application: "Application",
      backend: "Backend",
      cpuStats: "CPU Statistics",
      device: "Device",
      export: "Export",
      memStats: "Memoty Statistics",
      performance: "Performance",
      record: "Record",
      submit: "Submit",
      surface: "Surface",
      targetFps: "Target FPS",
    },
  },
};

export default exp;