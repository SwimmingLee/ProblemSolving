function solution(s) {
  var answer = "";
  for (var i = 1; i <= s.length; i++) {
    var compress_str = "";
    var count = 1;
    var stand_str = s.substr(0, i);
    for (var j = i; j + i <= s.length; j += i) {
      var cmp_str = s.substr(j, i);
      console.log("[] ", i, stand_str, " [] ", cmp_str);
      if (cmp_str === stand_str) count++;
      else {
        if (count > 1) {
          compress_str += toString(count);
          count = 1;
        }
        compress_str += stand_str;
        stand_str = cmp_str;
      }
    }
    if (count > 1) {
      compress_str += toString(count);
    }
    compress_str += stand_str;
    console.log(compress_str);
    if (!answer || compress_str.length < answer.length) answer = compress_str;
  }
  console.log(answer);
  return answer;
}

solution("sss");
