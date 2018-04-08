// This Script loads table.html every 500ms
// This Script is initialized in ModbusDataVisualizer.html
$(document).ready(function(){
        setInterval(function() {
            $("#modbusdata").load("table.html");
        }, 500);
    });