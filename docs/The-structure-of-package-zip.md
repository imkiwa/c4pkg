### The structure of package.zip

There are files listed below in each package.zip

```
package.zip/
  manifest.json
  data.zip
```

* `manifest.json` is a JSON format file which describes the package names, versions, dependencies and checksums.
* `data.zip`  is the real content that includes headers, libraries, binaries, useful programs and so on.

### The structure of data.zip
````
data.zip/
  bin/
  docs/
  include/
  lib/
```

* `bin/` put all binaries and useful programs here.
* `docs/` put all documents here. 
* `include/` put all headers here.
* `lib/` put all libraries here.
