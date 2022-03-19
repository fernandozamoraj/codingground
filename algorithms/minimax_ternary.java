class Node{
  public Node[] children;
  public int value;
  public String id;
  public Node(int value, String id){
    children = new Node[3];
    this.value = value;
    this.id = id;
  }
  public boolean isLeaf(){

    for(Node child: children){
      if(child != null){
        return false;
      }
    }

    return true;
  }
}

class Main {
  private static final int INFINITY = 9999; //9999 good enough for this
  public static void main(String[] args) {
    Node root = createTree();
    int max = minimax(root, 0, true, -INFINITY, INFINITY);
    System.out.println("Max is " + max);
  }

  private static Node createTree(){
    Node root = new Node(0, "root");

    Node n1 = new Node(-12, "n1");
    Node n2 = new Node(-12, "n2");
    Node n3 = new Node(10, "n3");
    Node n4 = new Node(-16, "n4");
    Node n5 = new Node(-6, "n5");
    Node n6 = new Node(15, "n5");
    Node n7 = new Node(-20, "n7");
    Node n8 = new Node(-6, "n8");
    Node n9 = new Node(5, "n9");
    

    Node minC1 = new Node(0, "minC1");
    Node minC2 = new Node(0, "minC2");
    Node minC3 = new Node(0, "minC3");

    minC1.children[0] = n1;
    minC1.children[1] = n2;
    minC1.children[2] = n3;

    minC2.children[0] = n4;
    minC2.children[1] = n5;
    minC2.children[2] = n6;

    minC3.children[0] = n7;
    minC3.children[1] = n8;
    minC3.children[2] = n9;

    root.children[0] = minC1;
    root.children[1] = minC2;
    root.children[2] = minC3;
    return root;
  }
  
  private static int max(int a, int b){
    if(a >= b){
      return a;
    }
    return b;
  }

  private static int min(int a, int b){
    if(a < b){
      return a;
    }
    return b;
  }
  
  private static int minimax(
    Node node, int depth, 
    boolean isMaximizingPlayer, 
    int alpha, int beta){

    if(node.isLeaf())
        return node.value;
    
    if(isMaximizingPlayer){
        int bestVal = -INFINITY; 
      
        for(Node childNode: node.children){
          if(childNode == null) continue;
          
          int value = minimax(childNode, depth+1, false, alpha, beta);
          bestVal = max( bestVal, value); 
          alpha = max(alpha, bestVal);
          if( beta <= alpha){
              System.out.println("Pruned at id: v/a/b " + node.id + ": " + value + "/" + alpha + "/" + beta);
              break;
          }

        }   
      
        return bestVal;
    }
    else{
        int bestVal = INFINITY;

        for(Node childNode: node.children){
            if(childNode == null) continue;
          
            int value = minimax(childNode, depth+1, true, alpha, beta);
            bestVal = min( bestVal, value);
            beta = min(beta, bestVal);
            if(beta <= alpha){
              System.out.println("Pruned at id: v/a/b " + node.id + ": " + value + "/" + alpha + "/" + beta);
              break;
            }
        }
      
        return bestVal;
    }
  }
}
