#include "imp_value.hh"

ImpValue::ImpValue() : type(NOTYPE) {}

ImpVType ImpValue::get_basic_type(string s)
{
  ImpVType tt;
  if (s.compare("int") == 0)
    tt = TINT;
  else if (s.compare("bool") == 0)
    tt = TBOOL;
  else if (s.compare("i32") == 0)
    tt = TI32;
  else if (s.compare("i64") == 0)
    tt = TI64;
  else
    tt = NOTYPE;
  return tt;
}

void ImpValue::set_default_value(ImpVType tt)
{
  type = tt;
  if (tt == TINT)
  {
    int_value = 0;
  }
  else if (tt == TBOOL)
  {
    bool_value = true;
  }
  else if (tt == TI32)
  {
    i32_value = 0;
  }
  else if (tt == TI64)
  {
    i64_value = 0;
  }
  else if (tt == TSTR)
  {
    string_value = "";
  }
  return;
}

std::ostream &operator<<(std::ostream &outs, const ImpValue &v)
{
  if (v.type == TINT)
  {

    outs << v.int_value;
  }
  else if (v.type == TI32)
  {

    outs << v.i32_value;
  }
  else if (v.type == TI64)
  {

    outs << v.i64_value;
  }
  else if (v.type == TBOOL)
  {
    if (v.bool_value)
      outs << "true";
    else
      outs << "false";
  }
  else
  {
    outs << "NOTYPE";
  }
  return outs;
}
