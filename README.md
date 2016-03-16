libtext_bayes
=============

Just Another Naive Bayes text classifier library


This is a example how to use Naive Bayes to classify SPAM messages, you can to use other purposes...

![Alt text](http://portolaplanet.com/wp-content/uploads/2013/10/dilbert-spam.gif)

Reference:
http://www.drdobbs.com/architecture-and-design/naive-bayesian-text-classification/184406064?pgno=1
https://coolerlab.wordpress.com/2015/03/29/trilhando-machine-learning/

TODO:
---
*Optimizing with inline ASM i think SiMD...

*Improve error handlers...

*fix bugs

...


How you can use ?
---

I test this lib at Linux, but run in MacOS,OpenBSD etc...


$ git clone https://github.com/CoolerVoid/libtext_bayes/


$ cd libtext_bayes; sudo sh install.sh; ./test

Source example at test.cpp, to compile you can follow this "g++ -o test test.cpp -llibtext_bayes"

```cpp
#include "libtext_bayes.h"
#include <iostream>

int main(int argc, char* argv[])
{
  NaiveBayes robot;

  robot.set_training_data_file(std::string("training_quotes3.txt")); // you can use external data to training
// you can pass each line but need use class SPAM,OK,GARBAGE at end of line etc...
  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");
  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");
  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");
  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");

  robot.train();
// test classification at random input
  std::string class_ = robot.classify(std::string("agora aproveite e compre"));
  std::cout << "High CLASS is " << class_ << std::endl;

  class_ = robot.classify(std::string("ola meu amigo como vai as coisas ?"));
  std::cout << "High CLASS is " << class_ << std::endl;

  class_ = robot.classify(std::string("videos porno apenas por 200 super barato"));
  std::cout << "High CLASS is " << class_ << std::endl;
 
  robot.free_bayers(); 

  return 0;
}
```
