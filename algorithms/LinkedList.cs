using System;

class MainClass {
  public static void Test(string actual, string expected){
    Console.WriteLine($"{actual} {expected}");
  }
  public static void Main (string[] args) {
    LinkedList<int> list = new LinkedList<int>();

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.PushBack(5);
    list.PushBack(6);
    list.PushBack(7);
    list.PushBack(8);
    list.PushBack(9);
    list.PushBack(10);

    Test($"{list.size()}", "should be 10");
    Test($"{list.PopBack()}", "should be 10");
    Test($"{list.PopFront()}", "should be 1");
    Test($"{list.PopBack()}", "should be 9");
    Test($"{list.PopFront()}", "should be 2");

    list = new LinkedList<int>();
    list.PushBack(1);
    list.PushBack(2);
    Test($"{list.PopFront()}", "should be 1");
    Test($"{list.PopBack()}", "should be 2");
    Test($"{list.size()}", "should be 0");
    Test($"{list.GetBack() == null}", "should be True");
    Test($"{list.GetFront() == null}", "should be True");

    list = new LinkedList<int>();
    list.PushBack(0);
    list.PushBack(1);
    list.PushBack(2);

    Node<int> current = list.GetFront();

    for(int i=0;i<list.size();i++){
      Test($"{current.data}", $"should be {i}" );
      current = current.next;
    }   
  }
}

class LinkedList<T>{

  Node<T> front;
  Node<T> back;
  int _size = 0;

  public Node<T> GetFront(){
    return front;
  }

  public Node<T> GetBack(){
    return back;
  }

  public int size(){
    return _size;
  }

  public bool isEmpty(){
    return _size == 0;
  }
  
  public void PushBack(T data){
    if(front == null){
      front = back = new Node<T>(data);
    }
    else{
      back.next = new Node<T>(data);
      back.next.previous = back;
      back = back.next;
    }
    _size++;
  }

  public void PushFront(T data){
    if(front == null){
      front = back = new Node<T>(data);
    }
    else{
      Node<T> temp = new Node<T>(data);
      temp.next = front;
      front = temp;
      temp.previous = front;
    }
    _size++;
  }

  public T PopBack(){
    T result = default(T);
    if(back != null){
      result = back.data;
      back = back.previous;

      if(back != null){
        back.next = null;
      }

      _size--;
      
      if(_size <= 1){
        front = back;
      }
    }
    return result;
  }

  public T PopFront(){
    T result = default(T);
    if(front != null){
      result = front.data;
      front = front.next;
      if(front != null){
        front.previous = null;
      }
      _size--;
      if(_size <= 1){
        back = front;
      }
    }

    return result;
  }
}

class Node<T>{
  public T data;
  public Node<T> next;
  public Node<T> previous;
  public Node(T data){
    this.data = data;
    this.next = null;
    this.previous = null;
  }
}