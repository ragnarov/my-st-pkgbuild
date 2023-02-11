typedef struct {
    int state;
    size_t length;
} URLdfa;

static int daddch(URLdfa *, char);

int daddch(URLdfa *dfa, char c)
{
	/* () and [] can appear in urls, but excluding them here will reduce false
	 * positives when figuring out where a given url ends.
	 */
	static const char URLCHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789-._~:/?#@!$&'*+,;=%";
	static const char RPFX[] = "//:sptth";

	if (!strchr(URLCHARS, c)) {
		dfa->length = 0;
		dfa->state = 0;

		return 0;
	}

	dfa->length++;

	if (dfa->state == 2 && c == '/') {
		dfa->state = 0;
	} else if (dfa->state == 3 && c == 'p') {
		dfa->state++;
	} else if (c != RPFX[dfa->state]) {
		dfa->state = 0;
		return 0;
	}

	if (dfa->state++ == 7) {
		dfa->state = 0;
		return 1;
	}

	return 0;
}

/*
** Select and copy the previous url on screen (do nothing if there's no url).
*/

void
copyurl(const Arg *arg) {
	int row = 0, /* row of current URL */
		col = 0, /* column of current URL start */
		colend = 0, /* column of last occurrence */
		passes = 0; /* how many rows have been scanned */

	const char *c = NULL,
		 *match = NULL;
	URLdfa dfa = { 0 };

	row = (sel.ob.x >= 0 && sel.nb.y > 0) ? sel.nb.y : term.bot;
	LIMIT(row, term.top, term.bot);

	colend = (sel.ob.x >= 0 && sel.nb.y > 0) ? sel.nb.x : term.col;
	LIMIT(colend, 0, term.col);

	/*
	** Scan from (term.row - 1,term.col - 1) to (0,0) and find
	** next occurrance of a URL
	*/
	for (passes = 0; passes < term.row; passes++) {
		/* Read in each column of every row until
		** we hit previous occurrence of URL
		*/
		for (col = colend; col--;)
			if (daddch(&dfa, term.line[row][col].u < 128 ? term.line[row][col].u : ' '))
				break;

		if (col >= 0)
			break;

		if (--row < 0)
			row = term.row - 1;

		colend = term.col;
	}

	if (passes < term.row) {
		selstart(col, row, 0);
		selextend((col + dfa.length - 1) % term.col, row + (col + dfa.length - 1) / term.col, SEL_REGULAR, 0);
		selextend((col + dfa.length - 1) % term.col, row + (col + dfa.length - 1) / term.col, SEL_REGULAR, 1);
		xsetsel(getsel());
		xclipcopy();
	}
}
