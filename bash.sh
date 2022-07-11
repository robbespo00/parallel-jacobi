iterations=100
tolerance=-1
output_filename="test"
max_num_threads=32

for size in 1000 5000 15000; do

  for mode in "seq" "thr" "ff"; do
    if [ "$mode" = "seq" ]; then
      ./main.out ${mode} ${size} ${iterations} ${tolerance} ${output_filename}
    fi

    if [ "$mode" = "thr" ] || [ "$mode" = "ff" ]; then
      ./main.out ${mode} ${size} ${iterations} ${tolerance} ${output_filename} 1
      for((i = 2; i <= max_num_threads; i+=2)); do
        ./main.out ${mode} ${size} ${iterations} ${tolerance} ${output_filename} ${i}
      done

    fi

  done

done