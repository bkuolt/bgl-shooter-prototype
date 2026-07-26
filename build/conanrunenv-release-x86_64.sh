script_folder="/home/bastian/code/bgl-shooter-prototype/build"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
for v in LD_LIBRARY_PATH DYLD_LIBRARY_PATH ALSA_CONFIG_DIR
do
   is_defined="true"
   value=$(printenv $v) || is_defined="" || true
   if [ -n "$value" ] || [ -n "$is_defined" ]
   then
       echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
   else
       echo unset $v >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
   fi
done

export LD_LIBRARY_PATH="/home/bastian/.conan2/p/b/libgl9b569f45967fa/p/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
export DYLD_LIBRARY_PATH="/home/bastian/.conan2/p/b/libgl9b569f45967fa/p/lib${DYLD_LIBRARY_PATH:+:$DYLD_LIBRARY_PATH}"
export ALSA_CONFIG_DIR="/home/bastian/.conan2/p/b/libal2778a0492b637/p/res/alsa"