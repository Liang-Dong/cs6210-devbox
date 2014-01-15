# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

    # Project Development Machine
    config.vm.define "devbox" do |devbox|
        devbox.vm.box = "precise64"
        devbox.vm.box_url = "http://files.vagrantup.com/precise64.box"
        devbox.vm.hostname = "cs6210"
        devbox.vm.network :private_network, ip: "10.1.0.10"
        devbox.vm.synced_folder "./", "/project", type: "nfs"

        # Enable provisioning with Ansible
        config.vm.provision :ansible do |ansible|
            ansible.playbook = "devbox/site.yml"
            ansible.inventory_path = "devbox/hosts"
            #ansible.verbose = "v"
        end
    end

    # Provider(s) configuration
    config.vm.provider "virtualbox" do |v|
      v.memory = 1024
    end
end
