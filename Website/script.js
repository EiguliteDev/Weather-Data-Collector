var value1Elements = document.getElementsByClassName("value1");
// Add more data

function exportCsv() {
  var rows = document.querySelectorAll(".data-table tr");
  var content = [];

  rows.forEach(row => {
    var elements = row.querySelectorAll("td");
    var rowData = Array.from(elements).map(element => element.textContent);

    content.push(rowData.join(","));
  });

  var string = content.join("\n");

  var blob = new Blob([string], { type: "text/csv" });

  var link = document.createElement("a");
  link.href = URL.createObjectURL(blob);
  link.download = "weatherData.csv";
  link.click();
}

function addData(data) {
  var table = document.querySelector("#data-table tbody");

  var newTr = table.insertRow();

  var value1Td = newTr.insertCell();
  value1Td.classList.add("value1");
  value1Td.textContent = data.value1;
  
  // Add more data by duplicating and changing the names
}

function getData() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "data-fetch.php", true);
  xhr.onreadystatechange = function() {
    if (xhr.readyState === XMLHttpRequest.DONE) {
      if (xhr.status === 200) {
        var allData = JSON.parse(xhr.responseText);
        allData.forEach(function(data) {
          addData(data);
        });
      }
    }
  };
  xhr.send();
}

getData();
