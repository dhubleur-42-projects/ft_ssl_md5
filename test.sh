test_md5 () {
	echo "=================== Test $1 ==================="
	FT=$(echo $1 | ./ft_ssl md5 -q)
	echo "ft_ssl  md5: $FT"
	SSL=$(echo $1 | md5sum | cut -d ' ' -f 1)
	echo "openssl md5: $SSL"
	if [ "$FT" = "$SSL" ]; then
		echo "OK"
	else
		echo "KO"
	fi
}

test_sha256 () {
	echo "=================== Test $1 ==================="
	FT=$(echo $1 | ./ft_ssl sha256 -q)
	echo "ft_ssl  sha256: $FT"
	SSL=$(echo $1 | sha256sum | cut -d ' ' -f 1)
	echo "openssl sha256: $SSL"
	if [ "$FT" = "$SSL" ]; then
		echo "OK"
	else
		echo "KO"
	fi
}

test () {
	test_md5 $1
	test_sha256 $1
}

test $1
