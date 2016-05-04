#include "PiecewiseCurveBuilder.cpp"
//
// prototype : template method for calculating a fair swap rate
template <typename T> Rate GetSwapRate(Period swapMaturity, Date settlementDate, Period floatingLegTenor, 
 Handle<YieldTermStructure>& curveHandle, Calendar calendar, DayCounter fixedLegDayCount, Period fixedLegTenor);
// prototype : hard-coded printer for USD rates
void PrintUSDRates(Date settlementDate, Handle<YieldTermStructure>& curveHandle);
// prototype : hard-coded printer for CHF discount factors
void PrintCHFDiscountFactors(Date settlementDate, Handle<YieldTermStructure>& curveHandle);
void PrintGBPDiscountFactors(Date settlementDate, Handle<YieldTermStructure>& curveHandle);

//
int main()
{
 // create trade date
 Date tradeDate(5, January, 2016);
 Settings::instance().evaluationDate() = tradeDate;
 //
 // create relinkable handle for curve
 RelinkableHandle<YieldTermStructure> curveHandle;
 //
 // create stand-alone quotes from USD market data
 boost::shared_ptr<Quote> usd_quote_deposit_1W(new SimpleQuote(0.0038975));
 boost::shared_ptr<Quote> usd_quote_deposit_1M(new SimpleQuote(0.004295));
 boost::shared_ptr<Quote> usd_quote_deposit_2M(new SimpleQuote(0.005149));
 boost::shared_ptr<Quote> usd_quote_deposit_3M(new SimpleQuote(0.006127));
 boost::shared_ptr<Quote> usd_quote_fra_3M6M(new SimpleQuote(0.008253));
 boost::shared_ptr<Quote> usd_quote_fra_6M9M(new SimpleQuote(0.009065));
 boost::shared_ptr<Quote> usd_quote_fra_9M12M(new SimpleQuote(0.01059));
 boost::shared_ptr<Quote> usd_quote_swap_2Y(new SimpleQuote(0.011459));
 boost::shared_ptr<Quote> usd_quote_swap_3Y(new SimpleQuote(0.013745));
 boost::shared_ptr<Quote> usd_quote_swap_4Y(new SimpleQuote(0.015475));
 boost::shared_ptr<Quote> usd_quote_swap_5Y(new SimpleQuote(0.016895));
 boost::shared_ptr<Quote> usd_quote_swap_6Y(new SimpleQuote(0.01813));
 boost::shared_ptr<Quote> usd_quote_swap_7Y(new SimpleQuote(0.019195));
 boost::shared_ptr<Quote> usd_quote_swap_8Y(new SimpleQuote(0.020115));
 boost::shared_ptr<Quote> usd_quote_swap_9Y(new SimpleQuote(0.020905));
 boost::shared_ptr<Quote> usd_quote_swap_10Y(new SimpleQuote(0.021595));
 boost::shared_ptr<Quote> usd_quote_swap_11Y(new SimpleQuote(0.0222));
 boost::shared_ptr<Quote> usd_quote_swap_12Y(new SimpleQuote(0.022766));
 boost::shared_ptr<Quote> usd_quote_swap_15Y(new SimpleQuote(0.0239675));
 boost::shared_ptr<Quote> usd_quote_swap_20Y(new SimpleQuote(0.025105));
 boost::shared_ptr<Quote> usd_quote_swap_25Y(new SimpleQuote(0.025675));
 boost::shared_ptr<Quote> usd_quote_swap_30Y(new SimpleQuote(0.026015));
 boost::shared_ptr<Quote> usd_quote_swap_40Y(new SimpleQuote(0.026205));
 boost::shared_ptr<Quote> usd_quote_swap_50Y(new SimpleQuote(0.026045));
 //
 // create curve builder for USD Libor swap curve
 Date settlementDate = UnitedKingdom().advance(tradeDate, 2, Days);
 PiecewiseCurveBuilder<USDLibor> USDCurveBuilder(settlementDate, 
  UnitedKingdom(), Annual, Thirty360());
 //
 // add quotes (reference to shared pointer) into USD curve builder
 USDCurveBuilder.AddDeposit(usd_quote_deposit_1W, 1 * Weeks);
 USDCurveBuilder.AddDeposit(usd_quote_deposit_1M, 1 * Months);
 USDCurveBuilder.AddDeposit(usd_quote_deposit_2M, 2 * Months);
 USDCurveBuilder.AddDeposit(usd_quote_deposit_3M, 3 * Months);
 USDCurveBuilder.AddFRA(usd_quote_fra_3M6M, 3 * Months, 3 * Months);
 USDCurveBuilder.AddFRA(usd_quote_fra_6M9M, 6 * Months, 3 * Months);
 USDCurveBuilder.AddFRA(usd_quote_fra_9M12M, 9 * Months, 3 * Months);
 USDCurveBuilder.AddSwap(usd_quote_swap_2Y, 2 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_3Y, 3 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_4Y, 4 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_5Y, 5 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_6Y, 6 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_7Y, 7 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_8Y, 8 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_9Y, 9 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_10Y, 10 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_11Y, 11 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_12Y, 12 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_15Y, 15 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_20Y, 20 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_25Y, 25 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_30Y, 30 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_40Y, 40 * Years);
 USDCurveBuilder.AddSwap(usd_quote_swap_50Y, 50 * Years);
 //
 // get relinkable curve handle from USD curve builder and print rates
 curveHandle = USDCurveBuilder.GetCurveHandle();
 PrintUSDRates(settlementDate, curveHandle);
 //
 // modify existing USD quotes by shocking rates up by 100 bps
 Real bump = 0.01;
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_deposit_1W)->setValue(usd_quote_deposit_1W->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_deposit_1M)->setValue(usd_quote_deposit_1M->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_deposit_2M)->setValue(usd_quote_deposit_2M->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_deposit_3M)->setValue(usd_quote_deposit_3M->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_fra_3M6M)->setValue(usd_quote_fra_3M6M->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_fra_6M9M)->setValue(usd_quote_fra_6M9M->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_fra_9M12M)->setValue(usd_quote_fra_9M12M->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_2Y)->setValue(usd_quote_swap_2Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_3Y)->setValue(usd_quote_swap_3Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_4Y)->setValue(usd_quote_swap_4Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_5Y)->setValue(usd_quote_swap_5Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_6Y)->setValue(usd_quote_swap_6Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_7Y)->setValue(usd_quote_swap_7Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_8Y)->setValue(usd_quote_swap_8Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_9Y)->setValue(usd_quote_swap_9Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_10Y)->setValue(usd_quote_swap_10Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_11Y)->setValue(usd_quote_swap_11Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_12Y)->setValue(usd_quote_swap_12Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_15Y)->setValue(usd_quote_swap_15Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_20Y)->setValue(usd_quote_swap_20Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_25Y)->setValue(usd_quote_swap_25Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_30Y)->setValue(usd_quote_swap_30Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_40Y)->setValue(usd_quote_swap_40Y->value() + bump);
 boost::dynamic_pointer_cast<SimpleQuote>(usd_quote_swap_50Y)->setValue(usd_quote_swap_50Y->value() + bump);
 //
 // re-print USD rates
 PrintUSDRates(settlementDate, curveHandle);

 
 tradeDate = Date(2, May, 2016);
 Settings::instance().evaluationDate() = tradeDate;

 // create curve builder for CHF Libor swap curve
 settlementDate = UnitedKingdom().advance(tradeDate, 2, Days);
 PiecewiseCurveBuilder<GBPLibor> GBPCurveBuilder(settlementDate, 
												 UnitedKingdom(), Annual, Thirty360());


  // create stand-alone quotes from CHF market data
 boost::shared_ptr<Quote> gbp_quote_deposit_1W(new SimpleQuote(0.004563));
 boost::shared_ptr<Quote> gbp_quote_deposit_1M(new SimpleQuote(0.0050725));
 boost::shared_ptr<Quote> gbp_quote_deposit_2M(new SimpleQuote(0.0054825));
 boost::shared_ptr<Quote> gbp_quote_deposit_3M(new SimpleQuote(0.0059056));
 boost::shared_ptr<Quote> gbp_quote_swap_2Y(new SimpleQuote(0.008695));
 boost::shared_ptr<Quote> gbp_quote_swap_3Y(new SimpleQuote(0.009645));
 boost::shared_ptr<Quote> gbp_quote_swap_4Y(new SimpleQuote(0.010465));
 boost::shared_ptr<Quote> gbp_quote_swap_5Y(new SimpleQuote(0.01134));
 boost::shared_ptr<Quote> gbp_quote_swap_6Y(new SimpleQuote(0.01225));
 boost::shared_ptr<Quote> gbp_quote_swap_7Y(new SimpleQuote(0.013265));
 boost::shared_ptr<Quote> gbp_quote_swap_8Y(new SimpleQuote(0.014135));
 boost::shared_ptr<Quote> gbp_quote_swap_9Y(new SimpleQuote(0.01493));
 boost::shared_ptr<Quote> gbp_quote_swap_10Y(new SimpleQuote(0.01558));
 boost::shared_ptr<Quote> gbp_quote_swap_12Y(new SimpleQuote(0.01668));
 boost::shared_ptr<Quote> gbp_quote_swap_15Y(new SimpleQuote(0.01764));
 boost::shared_ptr<Quote> gbp_quote_swap_20Y(new SimpleQuote(0.018104));
 boost::shared_ptr<Quote> gbp_quote_swap_25Y(new SimpleQuote(0.017820));
 boost::shared_ptr<Quote> gbp_quote_swap_30Y(new SimpleQuote(0.017760));

 //
 // add quotes (reference to shared pointer) into CHF curve builder
 GBPCurveBuilder.AddDeposit(gbp_quote_deposit_1W, 1 * Weeks);
 GBPCurveBuilder.AddDeposit(gbp_quote_deposit_1M, 1 * Months);
 GBPCurveBuilder.AddDeposit(gbp_quote_deposit_2M, 2 * Months);
 GBPCurveBuilder.AddDeposit(gbp_quote_deposit_3M, 3 * Months);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_2Y, 2 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_3Y, 3 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_4Y, 4 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_5Y, 5 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_6Y, 6 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_7Y, 7 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_8Y, 8 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_9Y, 9 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_10Y, 10 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_12Y, 12 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_15Y, 15 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_20Y, 20 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_25Y, 25 * Years);
 GBPCurveBuilder.AddSwap(gbp_quote_swap_30Y, 30 * Years);
 //
 // get relinkable curve handle from CHF curve builder and print discount factors
 curveHandle = GBPCurveBuilder.GetCurveHandle();
 PrintGBPDiscountFactors(settlementDate, curveHandle);


 
 //
 //
 //
 // create stand-alone quotes from CHF market data
 boost::shared_ptr<Quote> chf_quote_deposit_1W(new SimpleQuote(-0.00827));
 boost::shared_ptr<Quote> chf_quote_deposit_1M(new SimpleQuote(-0.00798));
 boost::shared_ptr<Quote> chf_quote_deposit_2M(new SimpleQuote(-0.00785));
 boost::shared_ptr<Quote> chf_quote_deposit_3M(new SimpleQuote(-0.00756));
 boost::shared_ptr<Quote> chf_quote_deposit_6M(new SimpleQuote(-0.006896));
 boost::shared_ptr<Quote> chf_quote_fra_6M12M(new SimpleQuote(-0.007103));
 boost::shared_ptr<Quote> chf_quote_swap_2Y(new SimpleQuote(-0.0068355));
 boost::shared_ptr<Quote> chf_quote_swap_3Y(new SimpleQuote(-0.006125));
 boost::shared_ptr<Quote> chf_quote_swap_4Y(new SimpleQuote(-0.0050195));
 boost::shared_ptr<Quote> chf_quote_swap_5Y(new SimpleQuote(-0.003725));
 boost::shared_ptr<Quote> chf_quote_swap_6Y(new SimpleQuote(-0.002425));
 boost::shared_ptr<Quote> chf_quote_swap_7Y(new SimpleQuote(-0.0011885));
 boost::shared_ptr<Quote> chf_quote_swap_8Y(new SimpleQuote(-0.000094));
 boost::shared_ptr<Quote> chf_quote_swap_9Y(new SimpleQuote(0.0008755));
 boost::shared_ptr<Quote> chf_quote_swap_10Y(new SimpleQuote(0.0016365));
 boost::shared_ptr<Quote> chf_quote_swap_12Y(new SimpleQuote(0.003));
 boost::shared_ptr<Quote> chf_quote_swap_15Y(new SimpleQuote(0.004525));
 boost::shared_ptr<Quote> chf_quote_swap_20Y(new SimpleQuote(0.0063));
 boost::shared_ptr<Quote> chf_quote_swap_25Y(new SimpleQuote(0.00735));
 boost::shared_ptr<Quote> chf_quote_swap_30Y(new SimpleQuote(0.007825));
 //
 // create curve builder for CHF Libor swap curve
 settlementDate = UnitedKingdom().advance(tradeDate, 2, Days);
 PiecewiseCurveBuilder<CHFLibor> CHFCurveBuilder(settlementDate, 
  UnitedKingdom(), Annual, Thirty360());
 //
 // add quotes (reference to shared pointer) into CHF curve builder
 CHFCurveBuilder.AddDeposit(chf_quote_deposit_1W, 1 * Weeks);
 CHFCurveBuilder.AddDeposit(chf_quote_deposit_1M, 1 * Months);
 CHFCurveBuilder.AddDeposit(chf_quote_deposit_2M, 2 * Months);
 CHFCurveBuilder.AddDeposit(chf_quote_deposit_3M, 3 * Months);
 CHFCurveBuilder.AddDeposit(chf_quote_deposit_6M, 6 * Months);
 CHFCurveBuilder.AddFRA(chf_quote_fra_6M12M, 6 * Months, 6 * Months);
 CHFCurveBuilder.AddSwap(chf_quote_swap_2Y, 2 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_3Y, 3 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_4Y, 4 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_5Y, 5 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_6Y, 6 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_7Y, 7 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_8Y, 8 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_9Y, 9 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_10Y, 10 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_12Y, 12 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_15Y, 15 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_20Y, 20 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_25Y, 25 * Years);
 CHFCurveBuilder.AddSwap(chf_quote_swap_30Y, 30 * Years);
 //
 // get relinkable curve handle from CHF curve builder and print discount factors
 curveHandle = CHFCurveBuilder.GetCurveHandle();
 PrintCHFDiscountFactors(settlementDate, curveHandle);
 //
 //
 //
 // create another curve builder for CHF Libor swap curve
 settlementDate = UnitedKingdom().advance(tradeDate, 2, Days);
 PiecewiseCurveBuilder<CHFLibor> CHFCurveBuilder2(settlementDate, 
  UnitedKingdom(), Annual, Thirty360());
 //
 // add market rates directly into CHF curve builder
 CHFCurveBuilder2.AddDeposit(-0.00827, 1 * Weeks);
 CHFCurveBuilder2.AddDeposit(-0.00798, 1 * Months);
 CHFCurveBuilder2.AddDeposit(-0.00785, 2 * Months);
 CHFCurveBuilder2.AddDeposit(-0.00756, 3 * Months);
 CHFCurveBuilder2.AddDeposit(-0.006896, 6 * Months);
 CHFCurveBuilder2.AddFRA(-0.007103, 6 * Months, 6 * Months);
 CHFCurveBuilder2.AddSwap(-0.0068355, 2 * Years);
 CHFCurveBuilder2.AddSwap(-0.006125, 3 * Years);
 CHFCurveBuilder2.AddSwap(-0.0050195, 4 * Years);
 CHFCurveBuilder2.AddSwap(-0.003725, 5 * Years);
 CHFCurveBuilder2.AddSwap(-0.002425, 6 * Years);
 CHFCurveBuilder2.AddSwap(-0.0011885, 7 * Years);
 CHFCurveBuilder2.AddSwap(-0.000094, 8 * Years);
 CHFCurveBuilder2.AddSwap(0.0008755, 9 * Years);
 CHFCurveBuilder2.AddSwap(0.0016365, 10 * Years);
 CHFCurveBuilder2.AddSwap(0.003, 12 * Years);
 CHFCurveBuilder2.AddSwap(0.004525, 15 * Years);
 CHFCurveBuilder2.AddSwap(0.0063, 20 * Years);
 CHFCurveBuilder2.AddSwap(0.00735, 25 * Years);
 CHFCurveBuilder2.AddSwap(0.007825, 30 * Years);
 //
 // get relinkable curve handle from CHF curve builder and re-print discount factors
 curveHandle = CHFCurveBuilder2.GetCurveHandle();
 PrintCHFDiscountFactors(settlementDate, curveHandle);
 return 0;
}
//
template <typename T> Rate GetSwapRate(Period swapMaturity, Date settlementDate, Period floatingLegTenor, 
 Handle<YieldTermStructure>& curveHandle, Calendar calendar, DayCounter fixedLegDayCount, Period fixedLegTenor)
{
 // using quantlib factory method for building vanilla swap
 boost::shared_ptr<IborIndex> index(new T(floatingLegTenor, curveHandle));
 VanillaSwap swap = MakeVanillaSwap(swapMaturity, index)
  .withEffectiveDate(settlementDate)
  .withFixedLegCalendar(calendar)
  .withFixedLegConvention(index->businessDayConvention())
  .withFixedLegDayCount(fixedLegDayCount)
  .withFixedLegTenor(fixedLegTenor)
  .withFloatingLegCalendar(calendar);
 return swap.fairRate();
}
//
void PrintUSDRates(Date settlementDate, Handle<YieldTermStructure>& curveHandle)
{
 Calendar calendar = UnitedKingdom();
 std::cout << std::endl;
 // print USD deposit rates
 std::cout << curveHandle->zeroRate(calendar.adjust(settlementDate + 1 * Weeks), 
  Actual360(), Simple).rate() << std::endl;
 std::cout << curveHandle->zeroRate(calendar.adjust(settlementDate + 1 * Months), 
  Actual360(), Simple).rate() << std::endl;
 std::cout << curveHandle->zeroRate(calendar.adjust(settlementDate + 2 * Months), 
  Actual360(), Simple).rate() << std::endl;
 std::cout << curveHandle->zeroRate(calendar.adjust(settlementDate + 3 * Months), 
  Actual360(), Simple).rate() << std::endl;
 // print USD forward rates
 std::cout << curveHandle->forwardRate(calendar.adjust(settlementDate + 3 * Months), 
  calendar.adjust(settlementDate + 6 * Months), Actual360(), Simple).rate() << std::endl;
 std::cout << curveHandle->forwardRate(calendar.adjust(settlementDate + 6 * Months), 
  calendar.adjust(settlementDate + 9 * Months), Actual360(), Simple).rate() << std::endl;
 std::cout << curveHandle->forwardRate(calendar.adjust(settlementDate + 9 * Months), 
  calendar.adjust(settlementDate + 12 * Months), Actual360(), Simple).rate() << std::endl;
 // print USD swap rates
 std::cout << GetSwapRate<USDLibor>(2 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(3 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(4 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(5 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(6 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(7 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(8 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(9 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(10 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(11 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(12 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(15 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(20 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(25 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(30 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(40 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
 std::cout << GetSwapRate<USDLibor>(50 * Years, settlementDate, 3 * Months, 
  curveHandle, calendar, Thirty360(), 1 * Years) << std::endl;
}
//
void PrintCHFDiscountFactors(Date settlementDate, Handle<YieldTermStructure>& curveHandle)
{
 // print CHF discount factors for every 6 months up to 30 years
 std::cout << std::endl;
 for(unsigned int i = 1; i != 61; i++)
 {
  std::cout << curveHandle->discount(UnitedKingdom()
   .adjust(settlementDate + (6 * i) * Months)) << std::endl;
 }
}

void PrintGBPDiscountFactors(Date settlementDate, Handle<YieldTermStructure>& curveHandle)
{
 // print GBP discount factors for every 6 months up to 30 years
 std::cout << std::endl;
 for(unsigned int i = 1; i != 61; i++)
 {
  std::cout << curveHandle->discount(UnitedKingdom()
   .adjust(settlementDate + (6 * i) * Months)) << std::endl;
 }
}
