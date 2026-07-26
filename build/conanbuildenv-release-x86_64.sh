script_folder="/home/bastian/code/bgl-shooter-prototype/build"
echo "echo Restoring environment" > "$script_folder/deactivate_conanbuildenv-release-x86_64.sh"
for v in ACLOCAL_PATH
do
   is_defined="true"
   value=$(printenv $v) || is_defined="" || true
   if [ -n "$value" ] || [ -n "$is_defined" ]
   then
       echo export "$v='$value'" >> "$script_folder/deactivate_conanbuildenv-release-x86_64.sh"
   else
       echo unset $v >> "$script_folder/deactivate_conanbuildenv-release-x86_64.sh"
   fi
done

export ACLOCAL_PATH="${ACLOCAL_PATH:-}${ACLOCAL_PATH:+:}/home/bastian/.conan2/p/xorg-a7814e7f591fa/p/bin/share/aclocal"