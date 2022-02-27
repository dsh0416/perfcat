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
      device: "Device",
      export: "Export",
      performance: "Performance",
      record: "Record",
      submit: "Submit",
      window: "Window",
      target_fps: "Target FPS",
    },
  },
};

export default exp;
