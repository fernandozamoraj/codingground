function quickSort(items, begin, end){
  
  if(begin >= 0 && end >= 0 && begin < end){
    let pivot = partition(items, begin, end);
    quickSort(items, begin, pivot);
    quickSort(items, pivot+1, end);
  }
}

function partition(items, begin, end){
  
  let low = begin-1;
  let high = end+1;
  pivotValue = items[Math.floor((begin+end)/2)];
  
  while(true){
    
    do{
      low++;
    }
    while(items[low] < pivotValue);
  
    do{
      high--;
    }while(items[high] > pivotValue);
    
    if(low >= high){
      return high;
    }
    
    let temp = items[low];
    items[low] = items[high];
    items[high] = temp;
  }
}

function displayArray(items){
  let strValue = items.join(' ');
  console.log(strValue);
}

let items = ['z', 'x', 'y', 'a', 't', 'u', 'v', 'b', 'c', 'a', 'z'];

displayArray(items);
quickSort(items, 0, items.length-1);
displayArray(items);
