/*
  @copyright Steve Keen 2019
  @author Russell Standish
  This file is part of Minsky.

  Minsky is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Minsky is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Minsky.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "minskyRS.h"
#include "minsky.rcd"
#include "assetClass.h"
#include "assetClass.rcd"
#include "bookmark.rcd"
#include "canvas.rcd"
#include "dimension.rcd"
#include "evalGodley.rcd"
#include "group.rcd"
#include "item.rcd"
#include "noteBase.rcd"
#include "panopticon.rcd"
#include "plot.rcd"
#include "plotWidget.rcd"
#include "port.rcd"
#include "rungeKutta.rcd"
#include "selection.rcd"
#include "slider.rcd"
#include "SVGItem.rcd"
#include "tensorVal.rcd"
#include "variable.rcd"
#include "variableValue.rcd"
#include "variableType.rcd"
#include "variableValueRS.h"
#include "wire.rcd"
#include "minsky_epilogue.h"

namespace classdesc
{
  void RESTProcess(RESTProcess_t& t, const string& d, minsky::Minsky& m)
  {
    classdesc_access::access_RESTProcess<minsky::Minsky>()(t,d,m);
    t.add(d, new RESTProcessObject<minsky::Minsky>(m));
  }
}