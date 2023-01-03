import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'


export default defineConfig({
  plugins: [react()],

  build: {
    rollupOptions: {
      output: {
        dir: '../Firmware/SoftAP-SPIFFS-Manager/data',
        assetFileNames: 'styles.css',
        entryFileNames: 'main.js',
      }
    },

  }
  
})
