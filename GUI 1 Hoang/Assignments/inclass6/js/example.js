/*
        Name: Hoang Do
        Email: Hoang_Do@student.uml.edu
        Major:Computer Science, School : UMass Lowell, Class:   91.61 GUI Programming I
        Date created: Nov 12,2019
        Inclass ex 6: DOM functions
        Copyright [2019] by Hoang Do. All rights reserved. May be freely copied or excerpted for educational purposes with credit to the author.
*/

// ADD NEW ITEM TO END OF LIST
var ul = document.getElementsByTagName("UL");
var cream = document.createElement("li");
cream.appendChild(document.createTextNode("cream"));
cream.setAttribute("id", "five");
ul[0].appendChild(cream);

// ADD NEW ITEM START OF LIST
var kale = document.createElement("li");
kale.appendChild(document.createTextNode("kale"));
kale.setAttribute("id", "zero");
ul[0].insertBefore(kale, ul[0].childNodes[0]);

// ADD A CLASS OF COOL TO ALL LIST ITEMS
var li = document.getElementsByTagName("LI");
for (var i = 0; i < li.length; i++) {
    li[i].className = "cool";
}

// ADD NUMBER OF ITEMS IN THE LIST TO THE HEADING
var totalNumber = parseInt(li.length);
var header2 = document.getElementsByTagName("h2");
var span = document.createElement("span");
span.appendChild(document.createTextNode(totalNumber));
header2[0].appendChild(span);
