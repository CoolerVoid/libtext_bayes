libtext_bayes
=============

Just Another Naive Bayes text classifier library


This is a example how to use Naive Bayes to classify SPAM messages, you can use it for other purposes...

![Alt text](http://portolaplanet.com/wp-content/uploads/2013/10/dilbert-spam.gif)

Reference:
http://www.drdobbs.com/architecture-and-design/naive-bayesian-text-classification/184406064?pgno=1
https://coolerlab.wordpress.com/2015/03/29/trilhando-machine-learning/

TODO:
---
* Optimizing with inline ASM (I think do it by using SiMD)...  

* Improve error handlers...

* Fix bugs

...


How you can use ?
---

I test this lib at Linux, but run in MacOS,OpenBSD etc...


`$ git clone https://github.com/CoolerVoid/libtext_bayes/


$ cd libtext_bayes; sudo sh install.sh; ./test

Source example at test.cpp, to compile you can follow this "g++ -o test test.cpp -llibtext_bayes"

```cpp
/*
 Example how too use my library "Naive Bayers Text Classifier" 
 Author: Cooler_
 Contact: c00f3r[at]gmail[dot]com

*/
#include "libtext_bayes.h"
#include <iostream>

int main(int argc, char* argv[])
{
  NaiveBayes robot;

  robot.set_training_data_file(std::string("training_quotes3.txt"));

  robot.add_training_data("Hot girls for money SPAM");
  robot.add_training_data("nude girls for you SPAM");
  robot.add_training_data("more sexy for 24hours SPAM");
  robot.add_training_data("hey brow how are you ? OK");
  robot.add_training_data("do you have a OK");
  robot.add_training_data("you can help me cheers OK");
  robot.add_training_data("buy new car only today SPAM");
  robot.add_training_data("price of cars is low SPAM");
  robot.add_training_data("bangbus photos click here to access SPAM");
  robot.add_training_data("credit suisse OK");
  robot.add_training_data("paypal payment  OK");
  robot.add_training_data("my friend hello OK");
  robot.add_training_data("black friday SPAM");
  robot.add_training_data("tits and ass sex girls SPAM");
  robot.add_training_data("milfs of the sex day SPAM");
  robot.add_training_data("linux openbsd freebsd cpp programming coding code OK");
  robot.add_training_data("ibovespa iboc nasdaq nysy jones hedge gold OK");
  robot.add_training_data("you have new coin OK");
  robot.add_training_data("womans for sex SPAM");
  robot.add_training_data("you won bilion milion SPAM");
  robot.add_training_data("you have won milion SPAM");
  robot.add_training_data("my friends name OK");
  robot.add_training_data("its ok is not a joke here OK");

  robot.train();

  std::string class_ = robot.classify(std::string("sold of  the week"));
  std::cout << "High CLASS is " << class_ << std::endl;

  class_ = robot.classify(std::string("how areyou my friend"));
  std::cout << "High CLASS is " << class_ << std::endl;

  class_ = robot.classify(std::string("buy porn videos"));
  std::cout << "High CLASS is " << class_ << std::endl;
 
  robot.free_bayers(); 

  return 0;
}

```
