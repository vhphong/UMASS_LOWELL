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
//https://jsfiddle.net/EKBqy/
//http://jqueryui.com/tabs/#manipulation
//https://jqueryui.com/slider/#hotelrooms

$(function() {

    //add slider function
    addSlider();

    $("#tabs").tabs();
    //enable JQUERY UI interface
    create_tabs();
    //create tabs if user hit create button


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


    // Initialize form validation on the input form.
    // It has the name attribute "input_form"
    $("form[name='input_form']").validate({
        // Specify validation rules
        rules: {
            row_start: {
                required: true, //required input
                number: true, //has to be a number
                isInt: true, // has to be an integer
                lessThan: '#row_end', // start number has to be smaller than end number
                min: -10,
                max: 10,
            },
            col_start: {
                required: true,
                number: true,
                isInt: true,
                lessThan: '#col_end',
                min: -10,
                max: 10,
            },
            row_end: {
                required: true,
                number: true,
                isInt: true,
                greaterThan: '#row_start',
                min: -10,
                max: 10,
            },
            col_end: {
                required: true,
                number: true,
                isInt: true,
                greaterThan: '#col_start',
                min: -10,
                max: 10,
            }
        },

        // validation error messages
        messages: {
            row_start: {
                required: "Please Enter An Integer", //if no input
                number: "Please Enter An Integer", //if not an integer
                min: "Please enter an integer bigger than -10",
                max: "Please enter an integer smaller than 10",
            },
            row_end: {
                required: "Please Enter An Integer",
                number: "Please Enter An Integer",
                min: "Please enter an integer bigger than -10",
                max: "Please enter an integer smaller than 10",
            },
            col_start: {
                required: "Please Enter An Integer",
                number: "Please Enter An Integer",
                min: "Please enter an integer bigger than -10",
                max: "Please enter an integer smaller than 10",
            },
            col_end: {
                required: "Please Enter An Integer",
                number: "Please Enter An Integer",
                min: "Please enter an integer bigger than -10",
                max: "Please enter an integer smaller than 10",
            },
        },
        // if the form is valid, draw the table
        submitHandler: function(form) {
            generateTable();
        }
    });
});


function check_valid_form() {
    // create the table when all inputs are valid
    if ($("form#input_form").valid() == true) {
        $("form#input_form").submit();
    }
}


//  Create slider and its settings


function addSlider() {
    // slider ui for min row
    //Set min max for slider, 2 way binding
    $("#slider_row_start").slider({
        min: -10,
        max: 10,
        slide: function(event, ui) {
            $("#row_start").val(ui.value); //update value to input box
            check_valid_form(); //check for valid input
        }
    }); //change slider if user enter a number to input box
    $("#row_start").on("keyup", function() {
        check_valid_form(); //check if valid input
        $("#slider_row_start").slider("value", this.value); //update value if valid value
    });

    $("#slider_row_end").slider({
        min: -10,
        max: 10,
        slide: function(event, ui) {
            $("#row_end").val(ui.value);
            check_valid_form();
        }
    });
    $("#row_end").on("keyup", function() {
        check_valid_form();
        $("#slider_row_end").slider("value", this.value);
    });

    $("#slider_col_start").slider({
        min: -10,
        max: 10,
        slide: function(event, ui) {
            $("#col_start").val(ui.value);
            check_valid_form();
        }
    });
    $("#col_start").on("keyup", function() {
        check_valid_form();
        $("#slider_col_start").slider("value", this.value);
    });

    $("#slider_col_end").slider({
        min: -10,
        max: 10,
        slide: function(event, ui) {
            $("#col_end").val(ui.value);
            check_valid_form();
        }
    });
    $("#col_end").on("keyup", function() {
        check_valid_form();
        $("#slider_col_end").slider("value", this.value);
    });
}

//Create tabs to save table


function create_tabs() {
    $("#delete_button").click(function() {
        //delete all tab button
        var num_tabs = $('div#tabs ul li.tab').length;
        do {
            $("#child_tab").remove();
            $("#tab_" + num_tabs--).remove();
        } while ($("#tabs li").length > 1);
    });
    $("#submit_button").click(function() {
        // Check valid input before create tab
        if ($("form#input_form").valid() === true) {
            var num_tabs = $('div#tabs ul li.tab').length + 1;
            var row_start = Number(document.getElementById('row_start').value);
            var row_finish = Number(document.getElementById('row_end').value);
            var col_start = Number(document.getElementById('col_start').value);
            var col_finish = Number(document.getElementById('col_end').value);
            //make tabs header using input
            //appending list item
            $('ul').append(
                '<li id ="child_tab" class="tab"><a href="#tab_' + num_tabs + '">(' + row_start + ',' + row_finish + ') ' + '(' + col_start + ',' + col_finish + ')' + '</a>' + "<span class='ui-icon ui-icon-close' role='presentation'></span>" + '</li>');
            //appending the actual tab with the corresponding table
            $('#tabs').append(
                '<div id ="tab_' + num_tabs + '">' + $("#tableout").html() + '</div>');
            $('#tabs').tabs("refresh");
            // Close icon: removing single the tab
            $('#tabs').on("click", "span.ui-icon-close", function() {
                var panelId = $(this).closest("li").remove().attr("aria-controls");
                $("#" + panelId).remove();
                $("#tabs").tabs("refresh");
            });
        }
    });
}

//Create table function
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

    document.getElementById('tableout').innerHTML = "";
    document.getElementById('tableout').innerHTML = table; //push table content into element
}
