// v8test.js
const addon = require('./build/Release/gpio');

console.log('This should be eight:', addon.add("w1", 1000));
