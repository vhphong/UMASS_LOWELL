/*
Name: Hoang Do
Email: Hoang_Do@student.uml.edu
Major:Computer Science, School : UMass Lowell, Class:   91.61 GUI Programming I
Date created: Nov 30,2019
A6: Creating an Interactive Dynamic Table Using Jquery
Description: create a multiplication table dynamically given user input
for width and length, using Jquery for validation
Copyright [2019] by Hoang Do. All rights reserved. May be freely copied or excerpted for educational purposes with credit to the author.
*/
// learnt from
//https://www.webtrickshome.com/faq/how-to-display-error-message-in-html-form-with-javascript-form-validation-without-using-alert
//https://www.w3resource.com/javascript/form/non-empty-field.php
//http://stackoverflow.com/questions/14347177/how-can-i-validate-that-the-max-field-is-greater-than-the-min-field
//https://stackoverflow.com/questions/3885817/how-do-i-check-that-a-number-is-float-or-integer
//https://jqueryvalidation.org/validate/

$(function() {
    //Create a validation method for ending number to be bigger than starting number
    $.validator.addMethod("greaterThan", function(value, element, param) {
        var $max = $(param);
        if (this.settings.onfocusout) {
            //execute validation after out of focus
            $max.off(".validate-greaterThan").on("blur.validate-greaterThan", function() {
                $(element).valid();
                //valid color if return valid
            });
        }
        //return true if ending number number is bigger than Starting number, else display the message
        return isNaN(parseInt($max.val())) || parseInt(value) >= parseInt($max.val());
    }, "Ending number must be bigger than starting number");

    //Create a validation method for starting number to be smaller than ending number
    $.validator.addMethod("lessThan", function(value, element, param) {
        var $min = $(param);
        if (this.settings.onfocusout) {
            $min.off(".validate-lessThan").on("blur.validate-lessThan", function() {
                $(element).valid();
            });
        }
        //return true if start number  is smaller than end number, else display the message
        return isNaN(parseInt($min.val())) || parseInt(value) <= parseInt($min.val());
    }, "Starting number must be smaller than ending number");

      //Create a validation method for checking integer number
    $.validator.addMethod("isInt", function(value, element) {
        //return true if is int, else display the message
        return ((Number(value)) % 1 === 0);
    }, "Please Enter An Integer");

    //Create a validation method for checking integer number
  $.validator.addMethod("largeNum", function(value, element) {
      //return true if is int, else display the message
      return isNaN(parseInt(value)) || (Math.abs(parseInt(value)) <= 1000000);
  }, "Please Enter An Integer");

    //Create a validation method for checking the range of starting number and ending number not bigger than 100
    $.validator.addMethod("cRange", function(value, element, param) {
        var $max = $(param);
        if (this.settings.onfocusout) {
            $max.off(".validate-cRange").on("blur.validate-cRange", function() {
                $(element).valid();
                //valid color if return valid
            });
        }
        return isNaN(parseInt(value))|| isNaN(parseInt($max.val())) || (Math.abs(parseInt($max.val()) - (parseInt(value))) <= 100);
    });


    // Initialize form validation on the input form.
    // It has the name attribute "input_form"
    $("form[name='input_form']").validate({
        // Specify validation rules
        rules: {
            row_start: {
                required: true, //required input
                number: true, //has to be a number
                isInt: true, // has to be an integer
                largeNum: true, //not too large
                lessThan: '#row_end', // start number has to be smaller than end number
                cRange: '#row_end', //two number has to be in a range
            },
            col_start: {
                required: true,
                number: true,
                isInt: true,
                largeNum: true,
                lessThan: '#col_end',
                cRange: '#col_end',
            },
            row_end: {
                required: true,
                number: true,
                isInt: true,
                largeNum: true,
                greaterThan: '#row_start',
                cRange: '#row_start',
            },
            col_end: {
                required: true,
                number: true,
                isInt: true,
                largeNum: true,
                greaterThan: '#col_start',
                cRange: '#col_start',
            }
        },

        // validation error messages
        messages: {
            row_start: {
                required: "Please Enter An Integer", //if no input
                number: "Please Enter An Integer", //if not an integer
                cRange: "Out of range", //if two number out of cRange
                largeNum: "The number is too large", //if the number is too large
            },
            row_end: {
                required: "Please Enter An Integer",
                number: "Please Enter An Integer",
                cRange: "Out of range",
                largeNum: "The number is too large",
            },
            col_start: {
                required: "Please Enter An Integer",
                number: "Please Enter An Integer",
                cRange: "Out of range",
                largeNum: "The number is too large",
            },
            col_end: {
                required: "Please Enter An Integer",
                number: "Please Enter An Integer",
                cRange: "Out of range",
                largeNum: "The number is too large",
            },
        },
        // if the form is valid, draw the table
        submitHandler: function(form) {
            generateTable();
        }
    });
});

function generateTable() {
    var row_start = Number(document.getElementById('row_start').value);
    var row_finish = Number(document.getElementById('row_end').value);
    var col_start = Number(document.getElementById('col_start').value);
    var col_finish = Number(document.getElementById('col_end').value);

    var table = '<table>';
    //table variables
    var col_header_value = col_start;
    var row_header_value = row_start;

    for (var i = col_start; i <= col_finish + 1; i++) {
        table += '<tr>'; //create one row for table
        for (var j = row_start; j <= row_finish + 1; j++) {
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

    document.getElementById('tableout').innerHTML = table; //push table content into element
}
