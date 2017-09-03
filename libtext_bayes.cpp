/*
#    Copyright (C) 2014 libtext_bayes authors(Antonio Costa, Cooler_),
#    
#    This file is part of libtext_bayers
#    
#    libtext_bayes is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    libtext_bayes is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#    You should have received a copy of the GNU Lesser General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "libtext_bayes.h"
#include <float.h>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set> 
#include <sstream>   
#include <cstdlib>

double NaiveBayes::get_prob_for_class(const StringVector& input_attr, const std::string& class_label)
{
/*
   Calculate P(X|Ci)
   To calculate P(X|Ci) 
   needs Maximum Likehood Estimate(MLE) to calculate P(Xi|Ci).

   P(Xi|Ci) = Count(Xi AND Ci) / Count(Ci AND Ycounter), Ycounter = any word in ALL documents
   Ci = class_label here

   In statistics, maximum-likelihood estimation (MLE) is a method of estimating the parameters 
   of a statistical model. When applied to a data set and given a statistical model, maximum-likelihood 
   estimation provides estimates for the model's parameters.

   The method of maximum likelihood corresponds to many well-known estimation methods in statistics. 
   For example, one may be interested in the heights of adult female penguins, but be unable to measure 
   the height of every single penguin in a population due to cost or time constraints. Assuming that the 
   heights are normally (Gaussian) distributed with some unknown mean and variance, the mean and variance 
   can be estimated with MLE while only knowing the heights of some sample of the overall population. 
   MLE would accomplish this by taking the mean and variance as parameters and finding particular parametric 
   values that make the observed results the most probable (given the model).

   ref: http://en.wikipedia.org/wiki/Maximum_likelihood


*/
	double log_prob_x_given_ci = 0.0; // TODO: We will find log probabilities to avoid underflow
	int i=0;

	while (i < input_attr.size()) 
	{
		std::string attr = input_attr[i];
		double count_xi_ci = 0;
		MapSD* instance_map = class_attr_event[class_label];
		MapSD::const_iterator mci = instance_map->find(attr);

		if (mci != instance_map->end()) 
			count_xi_ci = mci->second;
    
/* 
	Added 1 to numerator and total_attr_count to denominator for try Laplace smoothing.
	Laplacian smoothing is an algorithm to smooth a polygonal mesh. For each 
	vertex in a mesh, a new position is chosen based on local information (such as 
	the position of neighbors) and the vertex is moved there. In the case that a mesh 
	is topologically a rectangular grid (that is, each internal vertex is connected 
	to four neighbors) then this operation produces the Laplacian of the mesh.
	ref: http://en.wikipedia.org/wiki/Laplacian_smoothing

TODO* improve SSE other way... i think make inline ASM
*/
		double temp = (double) unique_class_attr_counts[class_label];
		double prob_xi_given_ci = (double) (count_xi_ci + 1) / (double) (temp + total_unique_attr_count);
		log_prob_x_given_ci +=  log(prob_xi_given_ci);
		i++;
	}

	return (log(class_probs[class_label]) + log_prob_x_given_ci);
}



void NaiveBayes::get_training_data()
{
// TODO * add handle error at file...
	std::ifstream file(training_data_filepath.c_str());
	std::string line;
// get each line and split class (string blahblahblah blah SPAM, last word is the class 'SPAM')
	while (std::getline(file, line)) 
	{
		std::istringstream iss(line);
		std::string attr;
		StringVector sv;

		while (std::getline(iss, attr, DELIM)) 
			if(sv.size()<=1000)
				sv.push_back(attr);

// number max of classes is 128
		if(classes.size() <= 128)
			classes.push_back(sv.back()); 

		sv.pop_back();

		if(attributes.size()<=1000) 
			attributes.push_back(sv);
  	}
}



void NaiveBayes::set_training_data_file(std::string filepath)
{
	training_data_filepath = filepath;
}

/*
 I test with valgrind, so a liberate heap with 'delete', to eliminate memory leaks
 ref: http://valgrind.org/docs/manual/mc-manual.html


*/
void NaiveBayes::free_bayers()
{

	int counter=0;
	
	while (counter < attributes.size())
	{
		if(class_attr_pair_counts[classes[counter]]!=NULL)
		{ 
			delete class_attr_pair_counts[classes[counter]];
			class_attr_pair_counts[classes[counter]]=NULL;
		}
		counter++;
	}
	

	counter=0;

	while (counter < attributes.size()) 
	{
		if(class_attr_event[classes[counter]] != NULL)
		{
			delete class_attr_event[classes[counter]];	
			class_attr_event[classes[counter]]=NULL;
		}
		counter++;
	}
}

void NaiveBayes::add_training_data(std::string data)
{
	std::ofstream file;

	file.open(training_data_filepath.c_str(), std::ios_base::app);
	file << data << "\n"; 
	file.close();
}

std::string NaiveBayes::classify(const std::string& input_attr)
{
	std::string token;
	std::istringstream iss(input_attr);
	StringVector attr;
	int i = 0;

	while (std::getline(iss, token, DELIM))
		if(attr.size()<=1000) 
			attr.push_back(token);
  

	std::set<std::string> class_labels;
	StringVector::const_iterator Vector_Instance;
	double max_prob = -DBL_MAX; 
	std::string max_class;
	Vector_Instance = classes.begin();

	while (Vector_Instance != classes.end()) 
	{

		if (class_labels.find(*Vector_Instance) == class_labels.end()) 
		{
			double prob = get_prob_for_class(attr, *Vector_Instance);
			std::cout << "Probability of " << *Vector_Instance << " ::: input quote ::: " <<
			input_attr << " is " << prob << std::endl;

			if (prob > max_prob) 
			{
				max_prob = prob;
				max_class = *Vector_Instance;
			}

			class_labels.insert(*Vector_Instance); 
    		}
		++Vector_Instance;
  	}
   
	return max_class;
}


void NaiveBayes::train()
{
/*
Explain:
get training data (attributes value matrix of instances and a vector of
classes for each instance), compute P(Ci) and P(X|Ci).

input eature data in the following format like a "2-D array" or "hash table":

Instance1: Attr1, Attr2, ... Attr N
Instance2: Attr1, Attr2, ... Attr N
Instance3: Attr1, Attr2, ... Attr N
Instance4: Attr1, Attr2, ... Attr N
Instance5: Attr1, Attr2, ... Attr N
Instance6: Attr1, Attr2, ... Attr N
InstanceX: ...
class vector containing a class for each instance row.

*/
	get_training_data();

	StringVector::const_iterator Vector_Instance;
	Vector_Instance = classes.begin();

	while (Vector_Instance != classes.end()) 
	{
		if (class_counts.find(*Vector_Instance) == class_counts.end()) 
 			class_counts[*Vector_Instance] = 1;
		else 
 			class_counts[*Vector_Instance]++;
    
		Vector_Instance++;
	}

  // Calculate P(Ci)  
	int total_classes = classes.size();
	MapSD::const_iterator map_it = class_counts.begin();

	while ( map_it != class_counts.end())
	{ 
		class_probs[map_it->first] = (double) map_it->second / (double) total_classes;
		map_it++;
  	}

  // Save the counts of co-occurence of an attribute with a class
	total_unique_attr_count = 0;
	MapSI attr_counts;

	for (int counter = 0; counter < attributes.size(); ++counter) 
	{
		StringVector sv = attributes[counter];
		StringVector::const_iterator it;
		MapSI current_pairs;

		for (it = sv.begin(); it != sv.end(); ++it) 
			current_pairs[*it] = 0;
    

		for (it = sv.begin(); it != sv.end(); ++it) 
		{
			if (class_attr_event.find(classes[counter]) == class_attr_event.end()) 
			{
				class_attr_event[classes[counter]] = new MapSD; 
				(*class_attr_event[classes[counter]])[*it] = 1;
				current_pairs[*it] = 1;
 			} else {

 				MapSD* cur_map = class_attr_event[classes[counter]];

        			if ((*cur_map).find(*it) == (*cur_map).end()) 
          				(*cur_map)[*it] = 1;

        
        			if (current_pairs[*it] == 0) 
        			{
          				(*cur_map)[*it]++;
          				current_pairs[*it] = 1;
        			}
     	 		}

      			if (attr_counts.find(*it) == attr_counts.end())
      			{
        			attr_counts[*it] = 1;
        			total_unique_attr_count++;
      			}
    		}
	}


	for (int counter = 0; counter < attributes.size(); ++counter) 
	{
		if (class_attr_pair_counts.find(classes[counter]) == class_attr_pair_counts.end()) 
			class_attr_pair_counts[classes[counter]] = new MapSD; 
    

		MapSD* msd = class_attr_pair_counts[classes[counter]];
		StringVector sv = attributes[counter];
		StringVector::const_iterator it;
 
		for (it = sv.begin(); it != sv.end(); ++it) 
			if ((*msd).find(*it) == (*msd).end()) 
				(*msd)[*it] = 1;
      
    
	}

	MapOfMaps::const_iterator mci = class_attr_pair_counts.begin();

  	while (mci != class_attr_pair_counts.end()) 
	{
		MapSD* msd = mci->second;
		double pair_count = 0;

		MapSD::const_iterator ci = (*msd).begin();

		while (ci != (*msd).end())
		{ 
			pair_count += ci->second;
			ci++;
    		}

		unique_class_attr_counts[mci->first] = pair_count;
//DEBUG  	std::cout << mci->first << ": " << pair_count << std::endl;
		mci++;
  	}

}

