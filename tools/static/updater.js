$(document).ready(function () {
  var socket = io.connect("http://" + document.domain + ":" + location.port);

  socket.on("connect", function () {
    socket.emit("am up", { data: "I'm connected!" });
  });
  socket.on("update", function (data) {
    let number = 0;
    deleteRows();
    size = data[1];
    table = data[0];
    for (let i = size - 1; i >= 0; --i) {
      const element = JSON.parse(table[i]);
      addRecords(element);
      addSection();
      number++;
    }
    var records = document.getElementById("number_of_records");
    animateValue(records, parseInt(records.innerHTML, 10), number, 200);
  });
  function addRecords(table) {
    for (let i of table) {
      addRow(i);
    }
  }
  function addSection() {
    var table = document.getElementById("myTableData");

    var rowCount = table.rows.length;
    var row = table.insertRow(rowCount);

    row.insertCell(0).innerHTML = "";
    row.insertCell(1).innerHTML = "";
    row.insertCell(2).innerHTML = "";
    row.insertCell(3).innerHTML = "";
    row.insertCell(4).innerHTML = "";
    row.insertCell(5).innerHTML = "";
  }
  function addRow(json) {
    var table = document.getElementById("myTableData");

    var rowCount = table.rows.length;
    var row = table.insertRow(rowCount);

    row.insertCell(0).innerHTML = json.name;
    row.insertCell(1).innerHTML = json.totalTime;
    row.insertCell(2).innerHTML = json.lastTime;
    row.insertCell(3).innerHTML = json.execnumber;
    row.insertCell(4).innerHTML = json.line;
    row.insertCell(5).innerHTML = json.path;
  }
  function addMasterRow(json) {
    var table = document.getElementById("myTableData");
    var header = table.createTHead();
    var row = header.insertRow(0);
    row.innerHTML =
      "<td><b>Name</b></td>\
      <td><b>Total Time(ms)</b></td> \
      <td><b>Last Time(ms)</b></td>\
      <td><b>Number of Executions</b></td>\
      <td><b>Line</b></td>\
      <td><b>Path</b></td>";
  }
  function deleteRows() {
    var Parent = document.getElementById("myTableData");
    while (Parent.hasChildNodes()) {
      Parent.removeChild(Parent.firstChild);
    }
    addMasterRow();
  }
  function animateValue(obj, start, end, duration) {
    let startTimestamp = null;
    const step = (timestamp) => {
      if (!startTimestamp) startTimestamp = timestamp;
      const progress = Math.min((timestamp - startTimestamp) / duration, 1);
      obj.innerHTML = Math.floor(progress * (end - start) + start);
      if (progress < 1) {
        window.requestAnimationFrame(step);
      }
    };
    window.requestAnimationFrame(step);
  }
});
