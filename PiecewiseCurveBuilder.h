// PiecewiseCurveBuilder.h
#include <ql/quantlib.hpp>
using namespace QuantLib;
//
template <class T>
class PiecewiseCurveBuilder
{
private:
 Date settlementDate;
 Calendar calendar;
 Frequency fixedLegFrequency;
 DayCounter dayCounter;
 DayCounter fixedLegDayCounter;
 BusinessDayConvention businessDayConvention;
 std::vector<boost::shared_ptr<RateHelper>> rateHelpers;
 boost::shared_ptr<YieldTermStructure> yieldTermStructure;
public:
 PiecewiseCurveBuilder(Date settlementDate, Calendar calendar, 
  Frequency fixedLegFrequency, DayCounter fixedLegDayCounter);
 void AddDeposit(boost::shared_ptr<Quote>& quote, Period periodLength);
 void AddDeposit(Rate quote, Period periodLength);
 void AddFRA(boost::shared_ptr<Quote>& quote, Period periodLengthToStart, Period periodLength);
 void AddFRA(Rate quote, Period periodLengthToStart, Period periodLength);
 void AddSwap(boost::shared_ptr<Quote>& quote, Period periodLength);
 void AddSwap(Rate quote, Period periodLength);
 RelinkableHandle<YieldTermStructure> GetCurveHandle();
};
