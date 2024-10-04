/*
Permission is hereby granted for the copying, distribution,
modification and use of this program and associated documentation
for recreational purposes, provided that all references to the
authors are retained.  However, permission is not and will not be
granted for the sale or promotional use of this program or program
documentation, or for use in any situation in which profit may be
considered an objective, since it is the desire of the authors to
respect the copyrights of the originators of the game.
 
This software and source code are distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, either express
or implied.
*/


#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "hamtrek.h"
#include "colors.h"

void attakreport(void) {
	if (future[FCDBAS] < 1e30) {
		proutn("Starbase in ");
		cramlc(1, batx, baty);
		prout(" is currently under attack.");
		proutn("It can hold out until Stardate ");
		cramf(future[FCDBAS], 0,1);
		prout(".");
	}
	if (isatb == 1) {
		proutn("Starbase in ");
		cramlc(1, d.isx, d.isy);
		prout(" is under Super-commander attack.");
		proutn("It can hold out until Stardate ");
		cramf(future[FSCDBAS], 0, 1);
		prout(".");
	}
}

void report(int f) {
	char *s1,*s2,*s3;

	chew();
	s1 = (thawed?"thawed ":"");
	switch (length) {
		case 1: s2="short"; break;
		case 2: s2="medium"; break;
		case 4: s2="long"; break;
		default: s2="unknown length"; break;
	}
	switch (skill) {
		case SNOVICE: s3="novice"; break;
		case SFAIR: s3="fair"; break;
		case SGOOD: s3="good"; break;
		case SEXPERT: s3="expert"; break;
		case SEMERITUS: s3="emeritus"; break;
		default: s3="skilled"; break;
	}
    
    clprintf("\n");
    printDialog(UHURA, " \"Report from Starfleet Command, Captian.\"\n");
    clprintf("%d Stardates remaining...", (int)intime);
    printf("\n  You %s playing a %s%s %s game.\n",
           alldone? "were": "are now", s1, s2, s3);
    if (skill>SGOOD && thawed && !alldone) prout("No plaque is allowed.");
    if (tourn) printf("This is tournament game %d.\n", tourn);
    if (f) printf("Your secret password is \"%s\"\n",passwd);
    
	printf("  %s[%s%d%s of %s%d%s]%s Klingon ships have been destroyed",
           clrwhite, clrbrgreen, d.killk+d.killc+d.nsckill, clrdefault,
           clrbrred, inkling, clrbrwhite, clrdefault);
	if (d.killc) printf(", including %s%d%s Commander%s.\n", clrbrgreen, d.killc, clrbrgreen, d.killc==1?"":"s");
	else if (d.killk+d.nsckill > 0) prout(", but no Commanders.");
	else prout(".");
	if (skill > SFAIR) printf("  - The Super Commander has %sbeen destroyed.\n",
						  d.nscrem?"not ":"");
	if (d.rembase != inbase) {
		proutn("There ");
		if (inbase-d.rembase==1) clprintf("has been %s1%s base", clrbrred, clrdefault);
		else {
			clprintf("have been %s", clrbrred);
			crami(inbase-d.rembase, 1);
			clprintf("%s bases", clrdefault);
		}
		clprintf(" destroyed, %s", clrbrgreen);
		crami(d.rembase, 1);
        clprintf("%s remaining.\n", clrdefault);
	}
	else printf("  There are %s%d%s bases.\n", clrbrgreen, inbase, clrdefault);
	if (REPORTS || iseenit) {
		/* Don't report this if not seen and
			either the radio is dead or not at base! */
		attakreport();
		iseenit = 1;
	}
	if (casual) printf("  %s%d%s casualt%s suffered so far.\n", clrbrred, casual, clrdefault, casual == 1 ? "y" : "ies");
#ifdef CAPTURE
    if (brigcapacity != brigfree)
    {
        printf("  %s%d%s Klingon%s in brig.\n", clrbrgreen,
               brigcapacity-brigfree, clrdefault, brigcapacity-brigfree>1 ? "s" : "");
    }
    if (kcaptured > 0)
    {
        printf("  %s%d%s captured Klingon%s turned in to Star Fleet.\n",
               clrbrgreen, kcaptured, clrdefault, kcaptured > 1 ? "s" : "");
    }
#endif
	if (nhelp) printf("  There %s %d call%s for help.\n",
					 nhelp==1 ? "was" : "were", nhelp, nhelp==1 ? "" : "s");
	if (ship == IHE) {
		proutn("  You have ");
		if (nprobes) crami(nprobes,1);
		else proutn("no");
		proutn(" deep space probe");
		if (nprobes!=1) proutn("s");
		prout(".");
	}
	if (REPORTS && future[FDSPROB] != 1e30) {
		if (isarmed) 
			clprintf("  An %sarmed deep space probe%s is in", clrbrred, clrdefault);
		else
			proutn("  A deep space probe is in");
		cramlc(1, probecx, probecy);
		prout(".");
	}
	if (icrystl) {
		if (cryprob <= .05)
			prout("  Dilithium crystals aboard ship...not yet used.");
		else {
			int i=0;
			double ai = 0.05;
			while (cryprob > ai) {
				ai *= 2.0;
				i++;
			}
			printf("  Dilithium crystals have been used %d time%s.\n",
				   i, i==1? "" : "s");
		}
	}
	skip(1);
}

void lrscan(void) {
	int x, y;
	chew();
	if (damage[DLRSENS] != 0.0) {
		/* Now allow base's sensors if docked */
		if (condit != IHDOCKED) {
			clprintf("%sLONG-RANGE SENSORS DAMAGED.%s", clrbrred, clrdefault);
			return;
		}
		skip(1);
        clprintf(" %s[%sLONG-RANGE SCAN%s]%s (Starbase Sensors)\n\n", clrbrwhite, clrbrgreen, clrbrwhite, clrdefault);
		// proutn("Starbase's long-range scan for");
	}
	else {
		skip(1);
        clprintf(" %s[%sLONG-RANGE SCAN%s]%s \n\n", clrbrwhite, clrbrgreen, clrbrwhite, clrdefault);
		// proutn("Long-range scan for");
	}
	cramlc(1, quadx, quady);
	skip(1);
	if (coordfixed)
	for (y = quady+1; y >= quady-1; y--) {
		for (x = quadx-1; x <= quadx+1; x++) {
			if(x == 0 || x > 8)
			{
				if(y > 0 && y <= 8) printf(" \u2501\u2501\u2501 ");
				else printf("     "); // side bars
			}
			else if(y == 0 || y > 8)
			{
				if(x > 0 && x <= 8) printf("  \u2503  "); // top/bottom bar
				else printf("     "); // side bars
			}
			else {
                ShowLRScanColors(d.galaxy[x][y]);
				printf("%5d", d.galaxy[x][y]);
				// If radio works, mark star chart so
				// it will show current information.
				// Otherwise mark with current
				// value which is fixed. 
				starch[x][y] = damage[DRADIO] > 0 ? d.galaxy[x][y]+1000 :1;
			}
		}
		putchar('\n');
	}
	else
	for (x = quadx-1; x <= quadx+1; x++) {
		for (y = quady-1; y <= quady+1; y++) {
			if(x == 0 || x > 8)
			{
				if(y > 0 && y <= 8) printf(" \u2501\u2501\u2501 ");
				else printf("     "); // side bars
			}
			else if(y == 0 || y > 8)
			{
				if(x > 0 && x <= 8) printf("  \u2503  "); // top/bottom bar
				else printf("     "); // side bars
			}
			else {
                ShowLRScanColors(d.galaxy[x][y]);
				// printf("%5d", d.galaxy[x][y]);
				// If radio works, mark star chart so
				// it will show current information.
				// Otherwise mark with current
				// value which is fixed. 
				starch[x][y] = damage[DRADIO] > 0 ? d.galaxy[x][y]+1000 :1;
			}
		}
		putchar('\n');
	}

}

void dreprt(void) {
	int jdam = FALSE, i;
	chew();

	for (i = 1; i <= ndevice; i++) {
		if (damage[i] > 0.0) {
			if (!jdam) {
				skip(1);
				prout("DEVICE            -REPAIR TIMES-");
				prout("                IN FLIGHT   DOCKED");
				jdam = TRUE;
			}
			printf("  %16s ", device[i]);
			if (i == DDRAY) { // Deathray is special case
				proutn("           ");
				cramf(damage[i]+0.005, 8, 2);
			} else {
				cramf(damage[i]+0.05, 8, 2);
				proutn("  ");
				cramf(docfac*damage[i]+0.005, 8, 2);
			}
			skip(1);
		}
	}
	if (!jdam) prout("All devices functional.");
}

void chart(int nn) {
	int i,j;

	chew();
	skip(1);
	if (stdamtim != 1e30 && stdamtim != d.date && condit == IHDOCKED) {
		printDialog(SPOCK, " \"I revised the Star Chart from the");
		prout("  starbase's records.\"");
		skip(1);
	}
	if (nn == 0)
	{
		clprintf(" %s[%sSTAR CHART%s]%s\n",
			clrbrwhite,
			clrbrgreen,
			clrbrwhite,
			clrdefault);
	}
	if (stdamtim != 1e30) {
		if (condit == IHDOCKED) {
			/* We are docked, so restore chart from base information -- these values won't update! */
			stdamtim = d.date;
			for (i=1; i <= 8 ; i++)
				for (j=1; j <= 8; j++)
					if (starch[i][j] == 1) starch[i][j] = d.galaxy[i][j]+1000;
		}
		else {
			proutn("(Last surveillance update ");
			cramf(d.date-stdamtim, 0, 1);
			prout(" stardates ago.)");
		}
	}
	if (nn ==0) skip(1);

	clprintf("%s      1    2    3    4    5    6    7    8%s\n", clrbrwhite, clrdefault);
	clprintf("%s    ----------------------------------------%s\n", clrpurple, clrdefault);
	// if (nn==0) prout("  -");
	if (coordfixed)
	for (j = 8; j >= 1; j--) {
		clprintf("%s%d %s-%s", clrbrwhite, j, clrpurple, clrblue);
		for (i = 1; i <= 8; i++) {
			if (starch[i][j] < 0) // We know only about the bases
				clprintf("%s  .%s1%s.", clrbrblue, clrbrcyan, clrbrblue);
				// printf("  .1.");
			else if (starch[i][j] == 0) // Unknown
				clprintf("%s  ...", clrbrblue);
			else if (starch[i][j] > 999) // Memorized value
				clprintf("%5d", starch[i][j]-1000);
			else
				ShowLRScanColors(d.galaxy[i][j]);
				// printf("%5d", d.galaxy[i][j]); // What is actually there (happens when value is 1)
		}
		clprintf("  %s-%s\n", clrpurple, clrdefault);
	}
	else
	for (i = 1; i <= 8; i++) {
		clprintf("%s%d %s-%s", clrbrwhite, i, clrpurple, clrblue);
		// printf("%d -", i);
		for (j = 1; j <= 8; j++) {
			if (starch[i][j] < 0) // We know only about the bases
				clprintf("%s  .%s1%s.", clrbrblue, clrbrcyan, clrbrblue);
				// printf("  .1.");
			else if (starch[i][j] == 0) // Unknown
				clprintf("%s  ...", clrbrblue);
			else if (starch[i][j] > 999) // Memorized value
				clprintf("%5d", starch[i][j]-1000);
			else
				ShowLRScanColors(d.galaxy[i][j]);
				// printf("%5d", d.galaxy[i][j]); // What is actually there (happens when value is 1)
		}
		clprintf("  %s-%s\n", clrpurple, clrdefault);
	}
	clprintf("%s    ----------------------------------------%s\n", clrpurple, clrdefault);
	if (nn == 0) {
		skip(1);
		crmshp();
		proutn(" is currently in");
		cramlc(1, quadx, quady);
		skip(1);
	}
}

void srscan(int l) {
	static char requests[][3] =
		{"","da","co","po","ls","wa","en","to","sh","kl","ti"};
	char *cp;
	int leftside=TRUE, rightside=TRUE, i, j, k=0, nn=FALSE;
	int goodScan=TRUE;
	switch (l) {
		case 1: // SRSCAN
			if (damage[DSRSENS] != 0) {
				/* Allow base's sensors if docked */
				if (condit != IHDOCKED) {
					prout("SHORT-RANGE SENSORS DAMAGED");
					goodScan=FALSE;
				}
				else
					prout("[Using starbase's sensors]");
			}
			if (goodScan)
				starch[quadx][quady] = damage[DRADIO]>0.0 ?
									   d.galaxy[quadx][quady]+1000:1;
			scan();
			if (isit("chart")) nn = TRUE;
			if (isit("no")) rightside = FALSE;
			chew();
			prout("\n    1 2 3 4 5 6 7 8 9 10");
			break;
		case 2: // REQUEST
			while (scan() == IHEOL)
				printf("Information desired? ");
			chew();
			for (k = 1; k <= 10; k++)
				if (strncmp(citem,requests[k],min(2,strlen(citem)))==0)
					break;
			if (k > 10) {
				prout("UNRECOGNIZED REQUEST. Legal requests are:\n"
					 "  date, condition, position, lsupport, warpfactor,\n"
					 "  energy, torpedoes, shields, klingons, time.");
				return;
			}
			// no "break"
		case 3: // STATUS
			chew();
			leftside = FALSE;
			skip(1);
	}
	for (i = 1; i <= 10; i++) {
		int jj = (k!=0 ? k : i);
		if (leftside) {
			if (coordfixed) {
				printf("%2d  ", 11-i);
				for (j = 1; j <= 10; j++) {
					if (goodScan || (abs((11-i)-secty)<= 1 && abs(j-sectx) <= 1))
					{
						SetSRScanColor(quad[j][11-i]);
						printf("%c ", quad[j][11-i]);
						DefaultGameColor();
					}
					else
						printf("- ");
				}
			} else {
				printf("%2d  ", i);
				for (j = 1; j <= 10; j++) {
					if (goodScan || (abs(i-sectx)<= 1 && abs(j-secty) <= 1))
					{
						SetSRScanColor(quad[i][j]);
						printf("%c ", quad[i][j]);
						DefaultGameColor();
					}
					else
						printf("- ");
				}
			}
		}
		if (rightside) {
			switch (jj) {
				case 1:
					printf(" Stardate      %.1f", d.date);
					break;
				case 2:
					if (condit != IHDOCKED) newcnd();
                    printf(" Condition     ");
                    switch (condit) {
                        case IHRED: clprintf("%sRED%s", clrbrred, clrdefault); break;
                        case IHGREEN: clprintf("%sGREEN%s", clrbrgreen, clrdefault);  break;
                        case IHYELLOW: clprintf("%sYELLOW%s", clrbryellow, clrdefault);  break;
                        case IHDOCKED: clprintf("%sDOCKED%s", clrbrblue, clrdefault); break;
                    }
//					switch (condit) {
//						case IHRED: cp = "RED"; break;
//						case IHGREEN: cp = "GREEN"; break;
//						case IHYELLOW: cp = "YELLOW"; break;
//						case IHDOCKED: cp = "DOCKED"; break;
//					}
#ifdef CLOAKING
				    if (iscloaked) clprintf(", %sCLOAKED%s", clrbrblack, clrdefault);
#endif
					break;
				case 3:
					printf(" Position     ");
					cramlc(0, quadx, quady);
					putchar(',');
					cramlc(0, sectx, secty);
					break;
				case 4:
					printf(" Life Support  ");
					if (damage[DLIFSUP] != 0.0) {
						if (condit == IHDOCKED)
							clprintf("%sDAMAGED%s, %ssupported by starbase%s", clrbrred, clrdefault, clrgreen, clrdefault);
						else
							clprintf("%sDAMAGED, reserves=%4.2f%s", clrbrred, lsupres, clrdefault);
					}
					else
						clprintf("%sACTIVE%s", clrbrblue, clrdefault);
					break;
				case 5:
					printf(" Warp Factor   %s%.1f%s", clrbrblue, warpfac, clrdefault);
					break;
				case 6:
					printf(" Energy        %s%.2f%s", clrbrblue, energy, clrdefault);
					break;
				case 7:
					printf(" Torpedoes     %s%d%s", clrbrblue, torps, clrdefault);
					break;
				case 8:
					printf(" Shields       ");
					if (damage[DSHIELD] != 0)
						clprintf("%sDAMAGED%s,", clrgreen, clrdefault);
					else if (shldup)
						clprintf("%sUP%s,", clrbrgreen, clrdefault);
					else
						clprintf("%sDOWN%s,", clrbrblue, clrdefault);

                    int shieldratio = (int)((100.0*shield)/inshld + 0.5);
                    if(shieldratio < 20) clprintf("%s", clrbrred);
                    else if(shieldratio < 60) clprintf("%s", clrbryellow);
                    else clprintf("%s", clrbrgreen);
                    clprintf(" %d%% %s%.1f units", shieldratio, clrdefault, shield);
					break;
				case 9:
					printf(" Klingons Left %s%d%s", clrbrred, d.remkl, clrdefault);
					break;
				case 10:
					printf(" Time Left     %s%.2f%s", clrbrblue, d.remtime, clrdefault);
					break;
			}
					
		}
		skip(1);
		if (k!=0) return;
	}
	if (nn) chart(1);
}

void eta(void) {
	int ix1, ix2, iy1, iy2, prompt=FALSE;
	int wfl;
	double ttime, twarp, tpower;
	if (damage[DCOMPTR] != 0.0) {
		prout("COMPUTER DAMAGED, USE A POCKET CALCULATOR.");
		skip(1);
		return;
	}
	if (scan() != IHREAL) {
		prompt = TRUE;
		chew();
		proutn("Destination quadrant and/or sector? ");
		if (scan()!=IHREAL) {
			huh();
			return;
		}
	}
	iy1 = aaitem +0.5;
	if (scan() != IHREAL) {
		huh();
		return;
	}
	ix1 = aaitem + 0.5;
	if (scan() == IHREAL) {
		iy2 = aaitem + 0.5;
		if (scan() != IHREAL) {
			huh();
			return;
		}
		ix2 = aaitem + 0.5;
	}
	else {	// same quadrant
		ix2 = ix1;
		iy2 = iy1;
		ix1 = quady;	// ya got me why x and y are reversed!
		iy1 = quadx;
	}

	if (ix1 > 8 || ix1 < 1 || iy1 > 8 || iy1 < 1 ||
		ix2 > 10 || ix2 < 1 || iy2 > 10 || iy2 < 1) {
		huh();
		return;
	}
	dist = sqrt(square(iy1-quadx+0.1*(iy2-sectx))+
				square(ix1-quady+0.1*(ix2-secty)));
	wfl = FALSE;

	if (prompt) prout("Answer \"no\" if you don't know the value:");
	while (TRUE) {
		chew();
		proutn("Time or arrival date? ");
		if (scan()==IHREAL) {
			ttime = aaitem;
			if (ttime > d.date) ttime -= d.date; // Actually a star date
			if (ttime <= 1e-10 ||
				(twarp=(floor(sqrt((10.0*dist)/ttime)*10.0)+1.0)/10.0) > 10) {
				prout("We'll never make it, sir.");
				chew();
				return;
			}
			if (twarp < 1.0) twarp = 1.0;
			break;
		}
		chew();
		proutn("Warp factor? ");
		if (scan()== IHREAL) {
			wfl = TRUE;
			twarp = aaitem;
			if (twarp<1.0 || twarp > 10.0) {
				huh();
				return;
			}
			break;
		}
		prout("Captain, certainly you can give me one of these.");
	}
	while (TRUE) {
		chew();
		ttime = (10.0*dist)/square(twarp);
		tpower = dist*twarp*twarp*twarp*(shldup+1);
		if (tpower >= energy) { // Suggestion from Ethan Staffin -- give amount needed
			prout("Insufficient energy, sir: we would need ");
			cramf(tpower, 1, 1);
			proutn (" units.");
			if (shldup==0 || tpower > energy*2.0) {
				if (!wfl) return;
				proutn("New warp factor to try? ");
				if (scan() == IHREAL) {
					wfl = TRUE;
					twarp = aaitem;
					if (twarp<1.0 || twarp > 10.0) {
						huh();
						return;
					}
					continue;
				}
				else {
					chew();
					skip(1);
					return;
				}
			}
			prout("But if you lower your shields,");
			proutn("remaining");
			tpower /= 2;
		}
		else
			proutn("Remaining");
		proutn(" energy will be ");
		cramf(energy-tpower, 1, 1);
		prout(".");
		if (wfl) {
			proutn("And we will arrive at stardate ");
			cramf(d.date+ttime, 1, 1);
			prout(".");
		}
		else if (twarp==1.0)
			prout("Any warp speed is adequate.");
		else {
			proutn("Minimum warp needed is ");
			cramf(twarp, 1, 2);
			skip(1);
			proutn("and we will arrive at stardate ");
			cramf(d.date+ttime, 1, 2);
			prout(".");
		}
		if (d.remtime < ttime)
			prout("Unfortunately, the Federation will be destroyed by then.");
		if (twarp > 6.0)
			prout("You'll be taking risks at that speed, Captain");
		if ((isatb==1 && d.isy == ix1 && d.isx == iy1 &&
			 future[FSCDBAS]< ttime+d.date)||
			(future[FCDBAS]<ttime+d.date && baty==ix1 && batx == iy1))
			prout("The starbase there will be destroyed by then.");
		proutn("New warp factor to try? ");
		if (scan() == IHREAL) {
			wfl = TRUE;
			twarp = aaitem;
			if (twarp<1.0 || twarp > 10.0) {
				huh();
				return;
			}
		}
		else {
			chew();
			skip(1);
			return;
		}
	}
			
}
