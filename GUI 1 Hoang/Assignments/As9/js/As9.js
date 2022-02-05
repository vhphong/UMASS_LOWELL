/*
    Name: Hoang Do
    Email: Hoang_Do@student.uml.edu
    Major:Computer Science, School : UMass Lowell, Class:   91.61 GUI Programming I
    Date created: Dec 18,2019
    A9: Scrabble
    Description: Implementing a Bit of Scrabble with Drag-and-Drop
    Copyright [2019] by Hoang Do. All rights reserved. May be freely copied or excerpted for educational purposes with credit to the author.
*/
// learnt from
//https://jesseheines.com/~heines/91.461/91.461-2015-16f/461-assn/
//https://medium.com/quick-code/simple-javascript-drag-drop-d044d8c5bed5
//http://yongcho.github.io/GUI-Programming-1/assignment9.html
//http://stackoverflow.com/questions/1527803/generating-random-numbers-in-javascript-in-a-specific-range
//https://en.wikipedia.org/wiki/Scrabble
//https://europeisnotdead.com/european-longest-words/

"use strict";
//Tile setup, and images
// From https://jesseheines.com/~heines/91.461/91.461-2015-16f/461-assn/
var scrabbleTiles = [] ;
scrabbleTiles["A"] = { "value" : 1,  "original-distribution" : 9,  "number-remaining" : 9, "image" : "img/Scrabble_Tile_A.jpg"  } ;
scrabbleTiles["B"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_B.jpg"  } ;
scrabbleTiles["C"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_C.jpg"  } ;
scrabbleTiles["D"] = { "value" : 2,  "original-distribution" : 4,  "number-remaining" : 4, "image" : "img/Scrabble_Tile_D.jpg"  } ;
scrabbleTiles["E"] = { "value" : 1,  "original-distribution" : 12, "number-remaining" : 12, "image" : "img/Scrabble_Tile_E.jpg"  } ;
scrabbleTiles["F"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_F.jpg"  } ;
scrabbleTiles["G"] = { "value" : 2,  "original-distribution" : 3,  "number-remaining" : 3, "image" : "img/Scrabble_Tile_G.jpg"  } ;
scrabbleTiles["H"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_H.jpg"  } ;
scrabbleTiles["I"] = { "value" : 1,  "original-distribution" : 9,  "number-remaining" : 9, "image" : "img/Scrabble_Tile_I.jpg"  } ;
scrabbleTiles["J"] = { "value" : 8,  "original-distribution" : 1,  "number-remaining" : 1, "image" : "img/Scrabble_Tile_J.jpg"  } ;
scrabbleTiles["K"] = { "value" : 5,  "original-distribution" : 1,  "number-remaining" : 1, "image" : "img/Scrabble_Tile_K.jpg"  } ;
scrabbleTiles["L"] = { "value" : 1,  "original-distribution" : 4,  "number-remaining" : 4, "image" : "img/Scrabble_Tile_L.jpg"  } ;
scrabbleTiles["M"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_M.jpg"  } ;
scrabbleTiles["N"] = { "value" : 1,  "original-distribution" : 6,  "number-remaining" : 6, "image" : "img/Scrabble_Tile_N.jpg"  } ;
scrabbleTiles["O"] = { "value" : 1,  "original-distribution" : 8,  "number-remaining" : 8, "image" : "img/Scrabble_Tile_O.jpg"  } ;
scrabbleTiles["P"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_P.jpg"  } ;
scrabbleTiles["Q"] = { "value" : 10, "original-distribution" : 1,  "number-remaining" : 1, "image" : "img/Scrabble_Tile_Q.jpg"  } ;
scrabbleTiles["R"] = { "value" : 1,  "original-distribution" : 6,  "number-remaining" : 6, "image" : "img/Scrabble_Tile_R.jpg"  } ;
scrabbleTiles["S"] = { "value" : 1,  "original-distribution" : 4,  "number-remaining" : 4, "image" : "img/Scrabble_Tile_S.jpg"  } ;
scrabbleTiles["T"] = { "value" : 1,  "original-distribution" : 6,  "number-remaining" : 6, "image" : "img/Scrabble_Tile_T.jpg"  } ;
scrabbleTiles["U"] = { "value" : 1,  "original-distribution" : 4,  "number-remaining" : 4, "image" : "img/Scrabble_Tile_U.jpg"  } ;
scrabbleTiles["V"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_V.jpg"  } ;
scrabbleTiles["W"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_W.jpg"  } ;
scrabbleTiles["X"] = { "value" : 8,  "original-distribution" : 1,  "number-remaining" : 1, "image" : "img/Scrabble_Tile_X.jpg"  } ;
scrabbleTiles["Y"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_Y.jpg"  } ;
scrabbleTiles["Z"] = { "value" : 10, "original-distribution" : 1,  "number-remaining" : 1, "image" : "img/Scrabble_Tile_Z.jpg"  } ;
scrabbleTiles["_"] = { "value" : 0,  "original-distribution" : 2,  "number-remaining" : 2, "image" : "img/Scrabble_Tile_Blank.jpg"  } ;

var scrabbleBoard = {};

// Setup for scrabbleBoard with image and property
// https://jesseheines.com/~heines/91.461/91.461-2015-16f/461-assn/
scrabbleBoard.slots = [];
scrabbleBoard.slots[0] = [];
//row 1
scrabbleBoard.slots[0][0] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[0][1] = { "wordMultiplier": 2, "letterMultiplier": 1, "image": "img/double_word.png"};
scrabbleBoard.slots[0][2] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[0][3] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[0][4] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[0][5] = { "wordMultiplier": 1, "letterMultiplier": 3, "image": "img/triple_letter.png"};
scrabbleBoard.slots[0][6] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};

//row 2
scrabbleBoard.slots[1] = [];
scrabbleBoard.slots[1][0] = { "wordMultiplier": 1, "letterMultiplier": 2, "image": "img/double_letter.png"};
scrabbleBoard.slots[1][1] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[1][2] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[1][3] = { "wordMultiplier": 3, "letterMultiplier": 1, "image": "img/triple_word.png"};
scrabbleBoard.slots[1][4] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[1][5] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[1][6] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};

//row 3
scrabbleBoard.slots[2] = [];
scrabbleBoard.slots[2][0] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[2][1] = { "wordMultiplier": 3, "letterMultiplier": 1, "image": "img/triple_word.png"};
scrabbleBoard.slots[2][2] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[2][3] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[2][4] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};
scrabbleBoard.slots[2][5] = { "wordMultiplier": 1, "letterMultiplier": 3, "image": "img/triple_letter.png"};
scrabbleBoard.slots[2][6] = { "wordMultiplier": 1, "letterMultiplier": 1, "image": "img/Scrabble_BlankSquare_81x87.jpg"};


// Globals to track current score.
var scrabbleScore = { "totalScore": 0, "score": 0};

// Calculates the score for each move and add up to total score.
scrabbleScore.calBS = function() {
  var eRow, eCol, letter, letterValue, wordMultiplier = 1, currentScore = 0;

  // Test word before update score
  if (!testWord()) {
    return 0;
  }

  // Mul the tile score  to the board multifier corresponding
  for (eRow = 0; eRow < 3; ++eRow) {
    for (eCol = 0; eCol < 7; ++eCol) {
      letter = scrabbleBoard.slots[eRow][eCol].letter;
      if (letter) {
        letterValue = scrabbleTiles[letter].value;
        currentScore += letterValue * scrabbleBoard.slots[eRow][eCol].letterMultiplier;
        wordMultiplier *= scrabbleBoard.slots[eRow][eCol].wordMultiplier;
      }
    }
  }
  currentScore *= wordMultiplier;

  //return the value after calculating
  return currentScore;
}

// update score to the ScoreBoard after calculating
scrabbleScore.refresh = function() {
  var currentScore = scrabbleScore.calBS();
  $("#score").css("color", "red");
  $("#score").html(currentScore);
}

// Add the score to the Total score and update new value
scrabbleScore.commit = function() {
  var currentScore = scrabbleScore.calBS();
  scrabbleScore.totalScore += currentScore;
  $("#tScore").html(scrabbleScore.totalScore);
  if (scrabbleScore.totalScore > 0) {
    $("#tScore").css("color", "green");
  }
}

// Restart the game, change the score and total score to 0
scrabbleScore.restart = function() {
  scrabbleScore.totalScore = 0;
  $("#score").html(0);
}

// Construct the board game
scrabbleBoard.makeBoard = function() {
  var row, col, imgPath, slot;

  // Set the board hight corresponding to row
  $("#ScarbbleBoard").css("height", 273);
  // Set the board hight corresponding to row
  $("#ScarbbleBoard").css("width", 595);

  // Lay down the board images.
  for (row = 0; row < 3; ++row) {
    for (col = 0; col < 7; ++col) {
      imgPath = scrabbleBoard.slots[row][col].image;
      slot = $("<div class=\"boardSlot\" row=\"" + row + "\" col=\"" + col + "\" style=\"background-image: url(" + imgPath + ")\" />");
      $("#ScarbbleBoard").append(slot);
      slot.css({"width": 81, "height": 87, "margin": 1, "border-width": 1});
    }
  }
}

  // Restart the game, remove all the tiles on the board
  scrabbleBoard.resetBoard = function() {
  var eRow, eCol;
  $("#ScarbbleBoard img").remove();

  // Reset the slot data structure.
  for (eRow = 0; eRow < 3; ++eRow) {
    for (eCol = 0; eCol < 7; ++eCol) {
      delete scrabbleBoard.slots[eRow][eCol].tileId;
      delete scrabbleBoard.slots[eRow][eCol].letter;
    }
  }
}

// get the ID of the tile from the slot
scrabbleBoard.tileID = function(row, col) {
  return scrabbleBoard.slots[row][col].tileId;
}

// Get the letter from the slot
scrabbleBoard.getLetter = function(row, col) {
  return scrabbleBoard.slots[row][col].letter;
}

// Check the slot is avilable or not
scrabbleBoard.isAvailable = function(row, col) {
  return typeof(scrabbleBoard.slots[row][col].tileId) === "undefined";
}

// Function add the tile to an available slot
scrabbleBoard.addTile = function(tileId, letter, row, col) {
  var eRow, eCol;

  // Move the tile to another slot
  for (eRow = 0; eRow < 3; ++eRow) {
    for (eCol = 0; eCol < 7; ++eCol) {
      if (scrabbleBoard.slots[eRow][eCol].tileId === tileId) {
        delete scrabbleBoard.slots[eRow][eCol].tileId;
        delete scrabbleBoard.slots[eRow][eCol].letter;
      }
    }
  }

  // Mark the slot that has the tile now
  scrabbleBoard.slots[row][col].letter = letter;
  scrabbleBoard.slots[row][col].tileId = tileId;
}

// Mark the slot that the tile has move out
scrabbleBoard.deleteFromSlot = function(row, col) {
  delete scrabbleBoard.slots[row][col].tileId;
  delete scrabbleBoard.slots[row][col].letter;
}

// Mark the position of the tile on the board
scrabbleBoard.findSlotFromTileId = function(tileId) {
  var eRow, eCol;
  for (eRow = 0; eRow < 3; ++eRow) {
    for (eCol = 0; eCol < 7; ++eCol) {
      if (scrabbleBoard.slots[eRow][eCol].tileId === tileId) {
        return [eRow, eCol];
      }
    }
  }
  return false;
}

// Get random n tile from deck and put it in the Deck. Decrease the number of Tile reamining in the Deck
function getFromDeck(n) {
  var pickTile = [];
  var allTiles = [];

  // Make an array of all remaining tiles for a random selection.
  for (var key in scrabbleTiles) {
    if (scrabbleTiles.hasOwnProperty(key)) {
      var remaining = scrabbleTiles[key]["number-remaining"];
      for (var i = 0; i < remaining; ++i) {
        allTiles.push(key);
      }
    }
  }

  // Pick n tile or all the tile if the remaining tiles less than n
  for (var i = 0; i < n; ++i) {
    if (allTiles.length) {
      var randomIndex = getRandomInt(0, Object.keys(allTiles).length - 1);
      var randomLetter = allTiles[randomIndex];
      pickTile.push(randomLetter);
      --scrabbleTiles[randomLetter]["number-remaining"];
      allTiles.splice(randomIndex, 1);
    }
  }
  // Update the remaining tiles on the page.
  $("#remainingTiles").html(allTiles.length);
  return pickTile;
}

// Total number of tile in Deck
function totalTile() {
  var numTotalTiles = 0;
  for (var key in scrabbleTiles) {
    if (scrabbleTiles.hasOwnProperty(key)) {
      numTotalTiles += scrabbleTiles[key]["number-remaining"];
    }
  }
  return numTotalTiles;
}

// Number of tile in the rack
function tileOnRack() {
  return $("#rack img").length;
}

// Restart the game
function restart() {
  // Clear the rack.
  $("#rack img").remove();

  // Remove all tiles from the board.
  scrabbleBoard.resetBoard();

  // Reset the number of tile
  for (var key in scrabbleTiles) {
    if (scrabbleTiles.hasOwnProperty(key)) {
      scrabbleTiles[key]["number-remaining"] = scrabbleTiles[key]["original-distribution"];
    }
  }

  scrabbleScore.restart();

  submit();
}

// Add the score to the total score, remove all the tile from the board. Refill random tiles from the deck to the rack
function submit() {
  var i, key, tileImageId, newTile, pickTile;

  scrabbleScore.commit();

  // reset the board.
  scrabbleBoard.resetBoard();

  // Refill random tiles from the deck to the rack
  pickTile = getFromDeck(7 - tileOnRack());
  for (i = 0; i < pickTile.length; ++i) {
    key = pickTile[i];
    tileImageId = generateTileId();
    newTile = $("<img id=\"" + tileImageId + "\" src=\"" + scrabbleTiles[key]["image"] + "\" class=\"lTile\" letter=\"" + key + "\" />");
    if (key == "_") {
      newTile.addClass("blankTile");
    }
    // Add tile image.
    $("#rack").append(newTile);
    //Set score to 0
    $("#score").html(0);

    // Add new css class that make the tile draggable
    newTile.addClass("tileRack");

    newTile.draggable({
      revertDuration: 400,
      start: function(event, ui) {
        // Tile will be on top of everything.
        $(this).css("z-index", 99);
        $(this).draggable("option", "revert", "invalid");
      },
      stop: function() {
        // revert z back to original after Tile drag
        $(this).css("z-index", "");
      }
    });
  }

  // Clear the word display after submit
  $("#word").html("");

  if (totalTile() == 0) {
    // Run out of Tile, Display the message
    document.getElementById("submitWord").disabled = false;
    $("#messages").css("color", "green");
    document.getElementById("messages").innerHTML = "Congratulation! You finish the whole game!!"
  } else {
    document.getElementById("submitWord").disabled = true;
  }
}

// Generates a unique string ID for tile.
function generateTileId() {
  var id;
  generateTileId.id = ++generateTileId.id || 1;
  id = "tile" + generateTileId.id.toString();
  return id;
}

// Returns a random integer in a rang [min, max]
function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Check the word spell in Dictionary
function checkDict(wd) {
  if (wd.length > 0 && checkDict.dict[wd]) {
    return true;
  }
  return false;
}
// The dictionary lookup object
checkDict.dict = {};
// Ajax request for Dictionary look up. Work only in web server.
$.ajax({
  url: 'dictionary.txt',
  success: function(result) {
    // Get an array of all the words.
    var words = result.split("\n");

    // Add them as properties to the dictionary lookup object.
    for (var i = 0; i < words.length; ++i) {
      checkDict.dict[words[i].toUpperCase()] = true;
    }
  }
});

// Test the word valid before the submit button enable to click.
function testWord() {
  var eRow, eCol , letter, errorCount, word = "", counter = [], marker =[];
  //counter letter for each row
  counter[0] = 0;
  counter[1] = 0;
  counter[2] = 0;
  errorCount = 0;
  // Add all the leter from the board to the word. Empty will be replace with "."
  for (eRow = 0; eRow < 3; ++eRow) {
    for (eCol = 0; eCol < 7; ++eCol) {
      letter = scrabbleBoard.getLetter(eRow, eCol);
      if (typeof(letter) === "undefined") {
        word += "\xB7";
      } else {
        word += letter;
        counter[eRow]++;
        marker[eRow] = eCol;
      }
    }

    //Check if those letter in the board sit next to each others, in one line (vertical or horizontal). Trim all the dots at the begining and at the end of the word
    if (counter[0] == 1 && counter[1] == 0 && counter[2] == 1 || (counter[0] == 1 && counter[1] == 1 && counter[2] == 1 && (marker[0] != marker[1] || marker[1] != marker[2])) ||(counter[0] == 1 && counter[1] == 1 && counter[2] == 0 && marker[0] != marker[1]) || (counter[0] == 0 && counter[1] == 1 && counter[2] == 1 && marker[1] != marker[2]) ) {
      errorCount = 10;
      break;
    } else if ((counter[0] > 1 && (counter[1] > 0 || counter[2] > 0)) || (counter[1] > 1 && (counter[0] > 0 || counter[2] > 0)) || (counter[2] > 1 && (counter[0] > 0 || counter[1] > 0))) {
      errorCount = 9;
      break;
    } else if (counter[0] > 0 ||counter[1] > 0 || counter[2] > 0) {
      word = word.replace(/^\xB7+/, "");
      word = word.replace(/\xB7+$/, "");
    }
 }

  //If the letter is in one line (vertical), trim all the dots between two letter
  if ((counter[0] == 1 && counter[1] == 1 && counter[2] == 0 && marker[0] == marker[1]) || (counter[0] == 0 && counter[1] == 1 && counter[2] == 1 && marker[1] == marker[2]) || (counter[0] == 1 && counter[1] == 1 && counter[2] == 1  && marker[0] == marker[1] && marker[1] == marker[2])){
    word = word.replace(/\xB7/gi, "");
  }

  //Display the word in html
  $("#word").html(word);

  // Check if the board is empty
  if (word == "") {
    checkSingleWord(false);
    errorCount = 8;
  } else {
    // Check for the gap between two letter (horizontal and vertical)
    var gapWord = new RegExp("[A-Z_]\xB7+[A-Z_]");
    if (gapWord.test(word)) {
      errorCount = 10;
    }
  }

  // Check if the word is at least two letters
  if (word.length <= 1 || word.length == 21) {
    errorCount = 6;
  }

  // Check if the word is valid in Dictionary
  if(errorCount == 0) {
    if (!checkDict(word)) {
      errorCount = 7;
    }
  }

  //Display the message corresponding to the errors
  if (errorCount == 0){
    $("#messages").css("color", "green");
    document.getElementById("messages").innerHTML = "Word is valid";
  }else if (errorCount == 6) {
    $("#messages").css("color", "red");
    document.getElementById("messages").innerHTML = "Need at least 2 letters to make a word";
  }else if (errorCount == 7) {
    $("#messages").css("color", "red");
    document.getElementById("messages").innerHTML = "Word is not in Dictionary. Please try another one!";
  }else if (errorCount == 8) {
    $("#messages").css("color", "red");
    document.getElementById("messages").innerHTML = "Nothing in the board!!";
  }else if (errorCount == 9) {
    $("#messages").css("color", "red");
    document.getElementById("messages").innerHTML = "Word should be in a line";
  }else if (errorCount == 10) {
    $("#messages").css("color", "red");
    document.getElementById("messages").innerHTML = "Letter need to place next to each other!";
  }

  //iF there is an error, can not submit the word
  if (errorCount) {
    document.getElementById("submitWord").disabled = true;
    $("#word").css("color", "red");
    return false;
  }

  $("#word").css("color", "green");
  document.getElementById("submitWord").disabled = false;

  return word;
}

//Blank Tile box open to choose a Tile
function blankTile(bTileChoose, tileId, row, col) {
  var tileSelect = $("<div id='blankTileDialog'></div>");
  var letterKey, newTile;
  for (letterKey in scrabbleTiles) {
    if (letterKey != "_") {
      // Add all tiles image to the box
      newTile = $("<img src='" + scrabbleTiles[letterKey]["image"] + "' class='tileBox' letter='" + letterKey + "'>");

      // Click event to choose a tile in the box
      newTile.click(function() {
        var newLetter = $(this).attr("letter");

        // Replace the image of the chosen tile to the blank
        bTileChoose.attr("letter", newLetter);
        bTileChoose.attr("src", scrabbleTiles[newLetter]["image"]);

        // Replace the tile ID
        tileId = bTileChoose.attr("id");
        scrabbleBoard.addTile(tileId, newLetter, row, col);

        testWord();
        scrabbleScore.refresh();
        //close the box
        tileSelect.dialog("close");
      });
      tileSelect.append(newTile);
    }
  }
  tileSelect.css("z-index", 100);
  tileSelect.dialog({
    modal: true,
    draggable: false,
    resizable: false
  });
}


$(window).on('load', function() {
  var row, col;
  //make the scrabbleBoard
  scrabbleBoard.makeBoard();

  // make the board droppable
  $(".boardSlot").droppable({

    accept: function(draggable) {
      var row, col;
      row = $(this).attr("row");
      col = $(this).attr("col");

      if (scrabbleBoard.tileID(row, col) === draggable.attr("id")) {
        // The tile will go back to the slot in a current range
        return true;
      } else if (scrabbleBoard.isAvailable(row, col)) {
        // The slot is available
        return true;
      } else {
        // The slot is not available
        return false;
      }
    },
    activeClass: "dragh",
    hoverClass: "hovertile",
    drop: function(event, ui) {
      var row, col, letter, word, tileId, previousPositionOnBoard;

      ui.draggable.removeClass("tileRack");
      ui.draggable.addClass("tileBoard");

      row = $(this).attr("row");
      col = $(this).attr("col");

      letter = ui.draggable.attr("letter");
      tileId = ui.draggable.attr("id");

      $(ui.draggable).css("top", "");
      $(ui.draggable).css("left", "");
      $(this).append(ui.draggable);

      // Open the box to choose tile when blank tile is place on the board.
      previousPositionOnBoard = scrabbleBoard.findSlotFromTileId(tileId);
      if ($(ui.draggable).hasClass("blankTile") && !previousPositionOnBoard) {

        blankTile($(ui.draggable), tileId, row, col);
      } else {
        scrabbleBoard.addTile(tileId, letter, row, col);
        testWord();
        scrabbleScore.refresh();
      }
    }
  });

  // Make the rack draggable and droppable
  $("#rack").droppable({
    activeClass: "dragh",
    hoverClass: "hovertile",
    tolerance: "touch",
    drop: function(event, ui) {
      var tileId, word, pos;

      ui.draggable.removeClass("tileBoard");
      ui.draggable.addClass("tileRack");

      // Change a blank tile back to blank when it move out the board to the rack
      if ($(ui.draggable).hasClass("blankTile")) {
        $(ui.draggable).attr("src", scrabbleTiles["_"]["image"]);
      }

      tileId = ui.draggable.attr("id");
      pos = scrabbleBoard.findSlotFromTileId(tileId);
      if (pos) {
        // Remove the mark of the tile move off the board
        scrabbleBoard.deleteFromSlot(pos[0], pos[1]);

        // Snap the tile image to the back of the rack.
        $("#rack").append(ui.draggable);
        ui.draggable.css({"position": "relative", "top": "", "left": ""});

        word = testWord();
        scrabbleScore.refresh();
      } else {
        // Tile go to the end of the rack when it come back from the board
        ui.draggable.draggable("option", "revert", true);
      }
    }
  });
  //start the game
  restart();
});
