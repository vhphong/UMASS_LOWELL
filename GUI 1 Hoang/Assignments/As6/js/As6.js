/*
Name: Hoang Do
Email: Hoang_Do@student.uml.edu
Major:Computer Science, School : UMass Lowell, Class:   91.61 GUI Programming I
Date created: Nov 11,2019
A6: Creating an Interactive Dynamic Table
Description: create a multiplication table dynamically given user input
for width and length
Copyright [2019] by Hoang Do. All rights reserved. May be freely copied or excerpted for educational purposes with credit to the author.
*/
// learnt from
//https://www.webtrickshome.com/faq/how-to-display-error-message-in-html-form-with-javascript-form-validation-without-using-alert
//https://www.w3resource.com/javascript/form/non-empty-field.php


function handleClicks() {
    $('#submit_button').click(function(event) {
        var row_start = Number(document.getElementById('row_start').value);
        var row_end = Number(document.getElementById('row_end').value);
        var col_start = Number(document.getElementById('col_start').value);
        var col_end = Number(document.getElementById('col_end').value);
        var error_check = 0;

        //Check if the input is an Integer and empty, limit the input from the user to 1,000,000
        if (!Number.isInteger(row_start) || checkNull(document.getElementById('row_start').value)) {
          document.getElementById('row_start_error').innerHTML = " Please Enter An Integer ";
          error_check = 1;
        } else if (row_start > 1000000) {
          document.getElementById('row_start_error').innerHTML = " The number is too large ";
          error_check = 1;
        } else {
          document.getElementById('row_start_error').innerHTML = "  ";
          error_check = 0;
        }

        if (!Number.isInteger(row_end) ||  checkNull(document.getElementById('row_end').value)) {
          document.getElementById('row_end_error').innerHTML = " Please Enter An Integer ";
          error_check = 1;
        } else if (row_end > 1000000) {
          document.getElementById('row_end_error').innerHTML = " The number is too large ";
          error_check = 1;
        } else {
          document.getElementById('row_end_error').innerHTML = " ";
        }

        if (!Number.isInteger(col_start) ||  checkNull(document.getElementById('col_start').value)) {
          document.getElementById('col_start_error').innerHTML = " Please Enter An Integer ";
          error_check = 1;
        } else if (col_start > 1000000) {
          document.getElementById('col_start_error').innerHTML = " The number is too large ";
          error_check = 1;
        } else {
          document.getElementById('col_start_error').innerHTML = "  ";
        }

        if (!Number.isInteger(col_end) ||  checkNull(document.getElementById('col_end').value)) {
          document.getElementById('col_end_error').innerHTML = " Please Enter An Integer ";
          error_check = 1;
        } else if (col_end > 1000000) {
          document.getElementById('col_end_error').innerHTML = " The number is too large ";
          error_check = 1;
        } else {
          document.getElementById('col_end_error').innerHTML = "  ";
        }


        //Check if the starting number less than ending numbers
        if (error_check == 0){
          if (row_start > row_end) {
            document.getElementById('row_start_error').innerHTML = " Starting number must be smaller than ending number ";
            document.getElementById('row_end_error').innerHTML = " Ending number must be bigger than starting number ";
            error_check = 1;
          } else {
            document.getElementById('row_start_error').innerHTML = "  ";
            document.getElementById('row_end_error').innerHTML = "  ";
          }

          if (col_start > col_end) {
            document.getElementById('col_start_error').innerHTML = " Starting number must be smaller than ending number ";
            document.getElementById('col_end_error').innerHTML = " Ending number must be bigger than starting number ";
            error_check = 1;
          } else {
            document.getElementById('col_start_error').innerHTML = "  ";
            document.getElementById('col_end_error').innerHTML = "  ";
          }
        } else {
          return false;
        }

        //Check if the two numbers are in range or in the limit
        if (error_check == 0){
          if (row_end -row_start > 100) {
            document.getElementById('row_start_error').innerHTML = " Out of range ";
            document.getElementById('row_end_error').innerHTML = " Out of range ";
            error_check = 1;
          } else {
            document.getElementById('row_start_error').innerHTML = "  ";
            document.getElementById('row_end_error').innerHTML = "  ";
          }

          if (col_end - col_start > 100) {
            document.getElementById('col_start_error').innerHTML = " Out of range ";
            document.getElementById('col_end_error').innerHTML = " Out of range ";
            error_check = 1;
          } else {
            document.getElementById('col_start_error').innerHTML = "  ";
            document.getElementById('col_end_error').innerHTML = "  ";
          }
        } else {
            return false;
        }

    var table = '<table>';
    if(error_check == 0){
          var table = '<table>';
          //table variables
          var col_header_value = col_start;
          var row_header_value = row_start;

          for (var i = col_start; i <= col_end + 1; i++) {
              table += '<tr>'; //create one row for table
              for (var j = row_start; j <= row_end + 1; j++) {
                  if (i == col_start && j == row_start) {
                      //1 corner is empty
                      table += '<td>' + '' + '</td>'; //create a cell for table
                  } else if (i == col_start) {
                      //row header value
                      table += "<td class ='header'>" + row_header_value++ + '</td>';
                  } else if (j == row_start) {
                      // column header value
                      table += '<td >' + col_header_value++ + '</td>';
                  } else {
                      // The rest of the table items
                      if (i % 2 === 0 && j % 2 === 0 || (i % 2 !== 0 && j % 2 !== 0)) {
                          table += "<td class = 'both_even_or_odd'>" + ((i - 1) * (j - 1)) + '</td>';
                      } else {
                          table += "<td class = 'either_even_or_odd'>" + ((i - 1) * (j - 1)) + '</td>';
                      }
                  }
              }
              table += '</tr>'; // close tab for row of table
          }
          table += '</table>'; // close out table tag
   }
   document.getElementById('tableout').innerHTML = table; //push table content into html
   return false;
  });
}

//Check function if the input is empty
function checkNull(rs){
    if (rs === ""){
      return 1;
    }
    return 0;
}
$(handleClicks);
