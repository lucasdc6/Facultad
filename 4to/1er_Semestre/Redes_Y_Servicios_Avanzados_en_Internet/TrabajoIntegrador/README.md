## Ideas

Para el NAP, filtrar la entrada para aquellos que esten originados en un x03

```bash
#(config) ip as-path access-list NAP_TRAFIC permit _[0-9]04$
#(config) route-map FILTER_NAP deny 20
#(config-route-map) match as-path NAP_TRAFIC
```

En cuanto a mi salida, filtar los originados en mi propio AS

```bash
#(config) ip as-path access-list MY_TRAFIC permit _304$
#(config) route-map FILTER_NAP deny 20
#(config-route-map) match as-path MY_TRAFIC
```
