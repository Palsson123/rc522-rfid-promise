var rc522 = require('./build/Release/rc522');
console.log("swag");
rc522(function(rfidTagSerialNumber) {
	console.log(rfidTagSerialNumber);
});
