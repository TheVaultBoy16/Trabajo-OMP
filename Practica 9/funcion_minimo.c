float minimo(
    float v[], 
    float n
){
    int i;
    float min = v[0];
    for (i =1 ; i<n ; i++){
        if( v[i] < min){
            min=v[i];
        }
    }
    return min;
}