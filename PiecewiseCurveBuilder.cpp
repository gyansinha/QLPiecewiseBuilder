// PiecewiseCurveBuilder.cpp
#pragma once
#include "PiecewiseCurveBuilder.h"
//
template <class T>
PiecewiseCurveBuilder<T>::PiecewiseCurveBuilder(Date settlementDate, 
 Calendar calendar, Frequency fixedLegFrequency, DayCounter fixedLegDayCounter)
{
 this->settlementDate = settlementDate;
 this->calendar = calendar;
 this->fixedLegFrequency = fixedLegFrequency;
 this->fixedLegDayCounter = fixedLegDayCounter;
 boost::shared_ptr<IborIndex> index(new T(3 * Months));
 dayCounter = index->dayCounter();
 businessDayConvention = index->businessDayConvention();
}
template <class T>
void PiecewiseCurveBuilder<T>::AddDeposit(boost::shared_ptr<Quote>& quote, Period periodLength)
{
 // using third DepositRateHelper constructor
 boost::shared_ptr<RateHelper> rateHelper(new DepositRateHelper(
  Handle<Quote>(quote), boost::shared_ptr<IborIndex>(new T(periodLength))));
 rateHelpers.push_back(rateHelper);
}
template <class T>
void PiecewiseCurveBuilder<T>::AddDeposit(Rate quote, Period periodLength)
{
 // using second DepositRateHelper constructor
 boost::shared_ptr<RateHelper> rateHelper(new DepositRateHelper(
  quote, boost::shared_ptr<IborIndex>(new T(periodLength))));
 rateHelpers.push_back(rateHelper);
}
template <class T>
void PiecewiseCurveBuilder<T>::AddFRA(boost::shared_ptr<Quote>& quote, 
 Period periodLengthToStart, Period periodLength)
{
 // using seventh FraRateHelper constructor
 boost::shared_ptr<RateHelper> rateHelper(new FraRateHelper(
  Handle<Quote>(quote), periodLengthToStart, 
  boost::shared_ptr<IborIndex>(new T(periodLength))));
 rateHelpers.push_back(rateHelper); 
}
template <class T>
void PiecewiseCurveBuilder<T>::AddFRA(Rate quote, 
 Period periodLengthToStart, Period periodLength)
{
 // using third FraRateHelper constructor
 boost::shared_ptr<RateHelper> rateHelper(new FraRateHelper(
  quote, periodLengthToStart, 
  boost::shared_ptr<IborIndex>(new T(periodLength))));
 rateHelpers.push_back(rateHelper); 
}
template <class T>
void PiecewiseCurveBuilder<T>::AddSwap(boost::shared_ptr<Quote>& quote, 
 Period periodLength)
{
 // using fifth SwapRateHelper constructor
 boost::shared_ptr<IborIndex> index(new T(periodLength));
 boost::shared_ptr<RateHelper> rateHelper(new SwapRateHelper(
  Handle<Quote>(quote), periodLength, calendar, fixedLegFrequency, 
  businessDayConvention, fixedLegDayCounter, index));
 rateHelpers.push_back(rateHelper);
}
template <class T>
void PiecewiseCurveBuilder<T>::AddSwap(Rate quote, 
 Period periodLength)
{
 // using fourth SwapRateHelper constructor
 boost::shared_ptr<IborIndex> index(new T(periodLength));
 boost::shared_ptr<RateHelper> rateHelper(new SwapRateHelper(
  quote, periodLength, calendar, fixedLegFrequency, 
  businessDayConvention, fixedLegDayCounter, index));
 rateHelpers.push_back(rateHelper);
}
template <class T>
RelinkableHandle<YieldTermStructure> PiecewiseCurveBuilder<T>::GetCurveHandle()
{
 if(yieldTermStructure == NULL)
 {
  yieldTermStructure = boost::shared_ptr<YieldTermStructure>(
   new PiecewiseYieldCurve<Discount, LogLinear>(
   settlementDate, rateHelpers, dayCounter));
 }
 return RelinkableHandle<YieldTermStructure>(yieldTermStructure);
}
