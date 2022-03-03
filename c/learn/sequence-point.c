// the -Wsequence-point error
a = a++;
// is equivalent to
a++;

a[n] = b[n++];
// is equivalent to
n++;
a[n-1] = b[n];
// or
a[n] = b[n+1];
n++;

a[i++] = i;
// is equivalent to
i++;
a[i] = i;

