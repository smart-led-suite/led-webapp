// test.js
const addon = require('./build/Release/gpio');

console.log('This should be eight:', addon.add(17, 1000));
