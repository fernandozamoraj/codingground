public class ArrayListMain {
    public static void Test(String actual, String expected){
      System.out.println(actual + " " + expected);
    }
    public static void main(String[] args) {
      ArrayList<Integer> list = new ArrayList<Integer>();
  
      list.pushBack(0);
      list.pushBack(1);
      list.pushBack(2);
      list.pushBack(3);
      list.pushBack(4);
      list.pushFront(-1);
      
      Test(""+list.size(), "should be 6");
      Test(""+list.popBack(), "should b 4");
      Test(""+list.popBack(), "should b 3");
      Test(""+list.popBack(), "should b 2");
      Test(""+list.popFront(), "should b -1");
      Test(""+list.popBack(), "should be 1"); 
      Test(""+list.popBack(), "should be 0");   
      Test(""+list.size(), "should be 0");
  
      Queue<Integer> queue = new Queue();
  
      queue.enqueue(0);
      queue.enqueue(1);
      queue.enqueue(2);
  
      System.out.println("Queue tests");
      Test(""+queue.size(), "should be 3");
      Test(""+queue.dequeue(), "should be 0");
      Test(""+queue.dequeue(), "should be 1");
      Test(""+queue.dequeue(), "should be 2");
      Test(""+queue.size(), "should be 0");
  
      System.out.println("Stack tests");
      Stack<Integer> stack = new Stack<Integer>();
      Test(""+stack.size(), "Should be 0");
      stack.push(0);
      stack.push(1);
      stack.push(2);
      Test(""+stack.peek(), "should be 2");
      Test(""+stack.pop(), "should be 2");
      Test(""+stack.pop(), "should be 1");
      Test(""+stack.pop(), "should be 0");
      Test(""+stack.peek(), "should be null");
      Test(""+stack.size(), "should be 0");
      
      
      
  
    }
  }
  
  class Stack<T>{
    ArrayList<T> stack;
  
    public Stack(){
      stack = new ArrayList<T>(10);
    }
  
    public void push(T item){
      stack.pushBack(item);
    }
  
    public T pop(){
      return stack.popBack();
    }
  
    public int size(){
      return stack.size();
    }
  
    public T peek(){
      return stack.get(stack.size()-1);
    }
  }
  
  class Queue<T>{
    ArrayList<T> queue;
  
    public Queue(){
      queue = new ArrayList<T>();
    }
  
    public void enqueue(T item){
      queue.pushBack(item);
    }
  
    public T dequeue(){
      return queue.popFront();
    }
  
    public int size(){
      return queue.size();
    }
  
    public T peek(){
      return queue.get(0);
    }
  }
  
  class ArrayList<T>{
  
    private Object[] list = new Object[3];
    private int size = 0;
    private int front = -1;
    private int back = -1;
  
    public ArrayList(){
      size = 0;
      front = back = -1;
    }
  
    public ArrayList(int capacity){
      list = new Object[capacity];
    }
  
    public int size(){
      return this.size;
    }
  
    private int getBackPlusOne(){
  
      return (back + 1) % list.length;
    }
  
    private int getFrontPlusOne(){
      return (front + 1)  % list.length;
    }
  
    private int getFrontMinusOne(){
      //Special case where list not init
      if(front < 0){
        return 0;
      }
      if(front - 1 < 0){
        return list.length-1; 
      }
      return front-1;
    }
      
    private int getBackMinusOne(){
      if(back < 0){
        return back;
      }
      if(back - 1 < 0){
        return list.length-1; 
      }
      return back-1;
    }
  
    private void resize(){
      Object[] newList = new Object[list.length * 2];
  
      for(int i=0;i<list.length; i++){
        newList[i] = list[i];
      }
      list = newList;
    }
  
    public void pushBack(T item){
      if(item == null)
        return;
  
      if(size + 1 == list.length){
        resize();
      }
      back = getBackPlusOne();
      list[back] = item;
      size++;
      if(size <= 1 ){
        front = back;
      }
    }
  
    public void pushFront(T item){
      if(item == null)
        return;
  
      if(size + 2  == list.length){
        resize();
      }
      front = getFrontMinusOne();
      list[front] = item;
      size++;
      if(size <= 1 ){
        back = front;
      }
    }
  
    public T popBack(){
      T result = null;
      if(size > 0){
        result = (T)list[back];
        list[back] = null;
        back = getBackMinusOne();
        size--;
      }
  
      if(size <= 1 ){
        front = back;
      }
      return result;
    }
  
    public T popFront(){
      T result = null;
      if(size > 0){
        result = (T)list[front];
        list[front] = null;
        front = getFrontPlusOne();
        size--;
      }
      if(size <= 1){
        back = front;
      }
      return result;
    }
  
    public T get(int index){
      int trueFront = (front + index)%list.length;
      if(index >= 0 && index < size){
        return (T)list[trueFront];
      }
      return null;
    }
  }