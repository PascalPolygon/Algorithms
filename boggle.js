
var sampleBoggle = [

  ['A', 'R', '6', 'B'],
  ['L', 'P', 'I', 'N'],
  ['H', 'E', 'V', 'K'],
  ['O', 'Z', 'R', 'S'],
  //['H', 'E', 'V', 'K'],
  //['A', 'R', '6', 'B'],
  //['H', 'E', 'V', 'K'],
  //['L', 'P', 'I', 'N'],
];

//Helper object to calculate indices of adjacent cells.
//Also passes the need of an additional for loop in getAdjascentLetters function
var adjascent = [

  {i:-1, j:-1}, {i: 0, j:-1}, {i: 1, j:-1},
  {i:-1, j: 0},               {i: 1, j: 0},
  {i:-1, j: 1}, {i: 0, j: 1}, {i: 1, j: 1},

];


const rows = sampleBoggle.length; //number of rows
const cols = sampleBoggle[0].length; //number of cols


var visitedCells = new Array(rows).fill(false).map(() => new Array(cols).fill(false)); //Creating matrix to keep track of visited cells


var myWord = "6Rivers";
myWord = myWord.toUpperCase();
var foundString = "";

var start = new Date()
findWordInBoggle();
var end = new Date()-start;
console.log('in '+end/1000+' seconds');

function findWordInBoggle(){
  for(let i = 0; i < rows; i++){
    for (let j = 0; j < cols; j++){
      getAdjascentLetters(i, j);
    }
  }
}


function getAdjascentLetters(i, j){

  visitedCells[i][j] = true; //Set to true,  the loop below only checks non-visted cells
  foundString += sampleBoggle[i][j];
  let iNext, jNext;


  if (foundString == myWord)
    console.log('Found: '+ foundString);

  //Loop through adjacent cells
  for(let k = 0; k < 8; k++){ //There is a max of 8 adjacent cells
    iNext = i+adjascent[k].i;
    jNext = j+adjascent[k].j;
    if (iNext >= 0 && jNext >= 0 && iNext < rows && jNext < cols && !visitedCells[iNext][jNext]){
        getAdjascentLetters(iNext, jNext);
    }
  }

  foundString = foundString.slice(0, -1); //remove last added character
  visitedCells[i][j] = false; // current cell was not visited for next set of recursive calls


}
