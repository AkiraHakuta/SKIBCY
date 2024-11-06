/* header.h */

//fixedpoint combinators
[Y] |:= (B(SII)(CB(SII)));
[Z] |:= (B(SII)(CB(SII)));
[T] |:= (B'SI(SII))(B'SI(SII));
//The simplest fixed-point combinator, found by John Tromp, is
[Y''] |:= (SCI)(SB(C'S(CI)I));

//booleans
[tru] |= K;
[fls] |= (KI);
[and] |= (CC[fls]);
[or] |= (C(CI[tru]));
[not] |= (C(CI[fls])[tru]);

//church numerals
[0] |= [fls];
[succ] |= (SB);
[1] |= [succ][0];
[2] |= [succ][1];
[3] |= [succ][2];
[4] |= [succ][3];
[5] |= [succ][4];
[6] |= [succ][5];
[7] |= [succ][6];
[8] |= [succ][7];
[9] |= [succ][8];
[10] |= [succ][9];
[pred] |= (C(C(CI(C(CI[1])[succ]))(K[0]))[0]);
[iszero] |= (C(CI(K[fls]))[tru]);
[add] |= (BSB');
[mult] |= B;
[sub] |= (C(CI[pred]));
//[power]xy=y^x
[power] |= I;

//pairs
[pair] |= (BC(CI));
[fst] |= (CI[tru]);
[snd] |= (CI[fls]);

//lists
[cons] |= [pair];
[head] |= [fst];
[tail] |= [snd];
[nil] |= (K[tru]);
[isnil] |= (CI(K(K[fls])));
[nth] |= (B'B[head](C(CI[tail])));

//etc
[fact_x] |:= (S(C[iszero][1])(S[mult](B[fact_x][pred])));
[fact_fx] |= (B'S(C[iszero][1])(B'S[mult](CB[pred])));
[sum_list] |:= (S(C[isnil][0])(S'[add][head](B[sum_list][tail])));
[map] |:= (B'S(C[isnil][nil])(S'(S'[cons])(CB[head])(C(B'[map])[tail])));
[fold_left] |:= (B'(S'S)(C[isnil])(C(S'C'(BS'[fold_left])(C'CB'[head]))[tail]));
[max_x_y] |= (S'C(C'(S'[iszero])[sub]I)I);
[pick] |:= (S(C'S'[iszero][head])(C'(B'[pick])[pred][tail]));

//list example
/* [list2431] := [cons][2]([cons][4]([cons][3]([cons][1][nil]))) */
