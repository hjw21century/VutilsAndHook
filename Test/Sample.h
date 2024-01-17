#pragma once

#include <vu>

/**
 * Sample
 */

class Sample
{
public:
	Sample() {}
	virtual ~Sample() {}

	virtual vu::IResult init()
	{
		return vu::VU_OK;
	}

	virtual vu::IResult run()
	{
		return vu::VU_OK;
	}
};

/*

#include "Sample.h"

class Example : public Sample
{
public:
	virtual vu::IResult run();
};

vu::IResult Example::run()
{
  return vu::VU_OK;
}

*/

#define DEF_SAMPLE(sample)\
class sample ## _Sample : public Sample\
{\
public:\
  virtual vu::IResult run();\
};\
\
vu::IResult sample ## _Sample ::run()

/*

#pragma once

#include "Sample.h"

DEF_SAMPLE(Sample)
{
  // YOUR CODE HERE //

  return vu::VU_OK;
}

*/
