let combo = []
let keys = [1,2,3,4,5,6,7,8,9,10]

setInterval(function(){
  if(combo.length > 0){
    combo.shift();
  }
}, 100)

setInterval(function(){
  combo.push(Math.floor(Math.random()*10+1))
}, 20)

setInterval(function(){
  let win = checkWinCombo(combo);
  if(win){
    combo = []
  }
  
}, 10);

setInterval(function(){
            console.log(".");
            }, 3000)

function checkWinCombo(combo){
  
  if(combo[0] == 1 && combo[1] == 5){
    console.log("You win");
    return true;
  }
  
  return false;
}



