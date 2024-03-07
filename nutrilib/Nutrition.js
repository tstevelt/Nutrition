//     Nutrition Tracking Website
// 
//     Copyright (C)  2023-2024 Tom Stevelt
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as
//     published by the Free Software Foundation, either version 3 of the
//     License, or (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.
// 
//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

function LookupFood ()
{
	var elem = document.getElementById ( "AddFoodID" );

	if ( elem.value == '' )
	{
		alert ( "Enter partial food description to lookup" );
		return;
	}

	window.open ( 'LookupFood.cgi?lookup=' + elem.value + '&target=' + elem.id, 'lookup', 'screenX=30,screenY=30,width=640,height=500,resizable=1,menubar=0,scrollbars=1' );
}

function PopupWindow ( Width, Height, Filename )
{
	window.open ( Filename, 'popup', 'screenX=30,screenY=30,width=' + Width + ',height=' + Height + 'menubar=0,scrollbars=0' );
}

// diet, carb, protein, fat
// except Standard, from https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7190064/table/tbl1/?report=objectonly
// Mediterranean is same as standard. https://mediterraneandietguru.com/mediterranean-diet-macros/
let Diets = [
	[ 'S', 'Standard', 50, 20, 30 ],
	[ 'L', 'Low Carb', 30, 30, 40 ],
	[ 'M', 'Moderate', 55, 15, 30 ],
	[ 'F', 'Low Fat',  63, 17, 20 ],
	[ 'P', 'Paleo',    40, 30, 30 ],
	[ 'C', 'Conley',   44, 17, 39 ],

];

function CalcSuggMacro ()
{
	var valueActive = document.getElementById('ActivityLevel').value;
	var valueDiet = document.getElementById('SignupDiet').value;
	var valueGender = document.getElementById('SignupGender').value;
	var valueBirthdate = document.getElementById('SignupBirthdate').value;
	var valueBirthyear = valueBirthdate.substr(0,4);
	var valueCurryear = new Date().getFullYear();
	var valueAge = valueCurryear - valueBirthyear;
	var valueWeight = document.getElementById('SignupWeight').value;
	var valueHeight = document.getElementById('SignupHeight').value;
	var elemCalorie = document.getElementById('SignupCalorie');
	var elemCarb = document.getElementById('SignupCarb');
	var elemProtein = document.getElementById('SignupProtein');
	var elemFat = document.getElementById('SignupFat');
	var valueCalorie = 0;
	var valuePA = 0.0;
	var ndxDiet;

	if ( valueActive == '?' )
	{
		alert ( 'Please select an activity level' );
		return;
	}

	if ( valueDiet == '?' )
	{
		alert ( 'Please select a diet type' );
		return;
	}

	for ( ndxDiet = 0; ndxDiet < Diets.length; ndxDiet++ )
	{
		// console.log ( Diets[ndxDiet][1] );
		if ( Diets[ndxDiet][0] == valueDiet )
		{
			break;
		}
	}
	if ( ndxDiet >= Diets.length )
	{
		alert ( 'Could not find diet type = ' + valueDiet );
		return;
	}

	// alert ( 'year ' + valueBirthyear + ', age ' + valueAge );

	// following formula from:
	// https://www.aqua-calc.com/calculate/daily-calorie-needs
	valueWeight = valueWeight * 0.4535924;
	valueHeight = valueHeight * 0.0254;
	if ( valueGender == 'M' )
	{
		if ( valueActive == '1' )
		{
			valuePA = 1.0;
		}
		else if ( valueActive == '2' )
		{
			valuePA = 1.12;
		}
		else if ( valueActive == '3' )
		{
			valuePA = 1.27;
		}
		else if ( valueActive == '4' )
		{
			valuePA = 1.54;
		}
		// fixit -- height is not on screen
		valueCalorie  = 864 - 9.72 * valueAge + valuePA * (14.2 * valueWeight + 503 * valueHeight);
	}
	else
	{
		if ( valueActive == '1' )
		{
			valuePA = 1.0;
		}
		else if ( valueActive == '2' )
		{
			valuePA = 1.14;
		}
		else if ( valueActive == '3' )
		{
			valuePA = 1.27;
		}
		else if ( valueActive == '4' )
		{
			valuePA = 1.45;
		}
		valueCalorie  = 387 - 7.31 * valueAge + valuePA * (10.9 * valueWeight + 660.7 * valueHeight);
	}


	elemCalorie.value = Math.round(valueCalorie,0);

	/*
	https://www.livestrong.com/article/81042-calculate-percentage-calories-fat-carbohydrate/
		carb	4 cal per gram
		protein	4 cal per gram
		fat		9 cal per gram
	
	https://www.healthline.com/nutrition/best-macronutrient-ratio
		45% to 65% of their calories from carbs     -> 50
		10% to 35% of their calories from proteins  -> 20
		20% to 35% of their calories from fats      -> 30

	elemCarb.value    = Math.round(valueCalorie * 0.5 / 4.0,0);
	elemProtein.value = Math.round(valueCalorie * 0.2 / 4.0,0);
	elemFat.value     = Math.round(valueCalorie * 0.3 / 9.0,0);
	*/

	elemCarb.value    = Math.round(valueCalorie * Diets[ndxDiet][2] / 400.0, 0);
	elemProtein.value = Math.round(valueCalorie * Diets[ndxDiet][3] / 400.0, 0);
	elemFat.value     = Math.round(valueCalorie * Diets[ndxDiet][4] / 900.0, 0);


}
