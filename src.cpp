#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

float training_set[4][3]{
  {-1.0, -1.0, -1.0},
  {1.0, 1.0, -1.0},
  {-1.0, 1.0, 1.0},
  {1, -1, 1}
};


/***********************/
/*  HELPER FUNCTIONS */
/***********************/
void print_vec(vector<float> v)
{
  for(int i = 0; i < v.size(); i++)
    cout << v.at(i) << " ";
}

float random_f()
{
  return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2));
}

float dot(vector <float> v1, vector <float> v2)
{
  float scalar = 0.0;
  for(int i = 0; i < v1.size(); i++)
    scalar += v1.at(i) * v2.at(i);
  return scalar;
}

vector <float> mat_vec_mult(vector <vector <float>> w, vector <float> x)
{
  vector <float> v;
  for(int i = 0; i < w.size(); i++)
  {
    v.push_back(dot(w.at(i),x));
  }
  return v;
}

/***********************/
/*  STRUCT DEFINITIONS */
/***********************/
struct Node{

  vector <float> outgoing_weights;
  vector <float> input;


  void set_node_input(vector <float> node_input_vec)
  {
    for( int i = 0; i < node_input_vec.size(); i++)
      input.push_back(node_input_vec.at(i));
  }

  void set_outgoing_weights(int n)
  { //n is number of nodes in next layer.
    for(int i = 0; i < n; i++)
      outgoing_weights.push_back(random_f());
  }
};

struct Layer{
  vector <Node> layer_nodes;
  float bias = 1.0;

  void set_nodes(int nodes, int outgoing)
  {
    for(int i = 0; i < nodes; i++)
    {
      Node tmp;
      tmp.set_outgoing_weights(outgoing);
      layer_nodes.push_back(tmp);
    }
  }

};

//Bias is in here
struct Network{

  Layer Input, Hidden, Output;
  float hypothesis;
  vector <float> x_vec;

  vector < vector <float>> set_weight_matrix (Layer in, Layer out)
  {
    vector <vector<float>> w; //vector of float vectors

    for(int i = 0; i < out.layer_nodes.size(); i++)
    {
      vector <float> x_w;

      //For each node from the input layer
      for(int j =  0; j < in.layer_nodes.size(); j++)
      {
        x_w.push_back(in.layer_nodes.at(j).outgoing_weights.at(i));
      }
      w.push_back(x_w);
    }
    return w;
  }

  float feed_and_backpropagate(vector <float> x_vec, float y)
  {
    vector <float> z_2(4);
    vector <float> z_3(1);
    vector <vector <float>> w = set_weight_matrix(Input,Hidden);
    z_2 = mat_vec_mult(w,x_vec);

    for(int i = 0; i < z_2.size(); i++)
      z_2.at(i) += 1.0;

    for(int i = 0; i < z_2.size(); i++)
      z_2.at(i) = tanh(z_2.at(i));

    w = set_weight_matrix(Hidden, Output);
    z_3 = mat_vec_mult(w, z_3);

    for(int i = 0; i < z.size(); i++)
      hypothesis = z_3.at(i);

    float output_error = (1 - (y - hypothesis)) * pow((1- hypothesis),2);

    vector <float> layer_error;
    for(int i = 0; i < Hidden.layer_nodes.size(); i++)
    {
      layer_error.push_back((output_error*Hidden.layer_nodes.outgoing_weights.at(i)) * pow(1 - z_2.at(i)));
    }

    float weight_error

  }

};

/* DRIVER FUNCTION */

int main()
{
  vector <float> test;
  test.push_back(-1.0);
  test.push_back(-1.0);

  Network myANN;

  myANN.Input.set_nodes(2,4);
  myANN.Hidden.set_nodes(4,1);
  myANN.Output.set_nodes(1,0);

  myANN.feed_and_backpropagate(test, 1.0);


  return 0;
}
