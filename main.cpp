#include <iostream>
#include "cypher.h"
#include "interface.h"

#define PASSWORD "changethis"
#define CYPHER1_KEY "@fo5@N1Xy%&4o7l!a4p2"
#define CYPHER2_KEY "*%%k!oi6jV6*RsV!6@&Zh%!@j"

int main() {

	Interface root(PASSWORD, CYPHER1_KEY, CYPHER2_KEY);
	root.start();

	return 0;
}