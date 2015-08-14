/*
 * Copyright (C) 2009, Lars-Peter Clausen <lars@metafoo.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/of.h>
#include <linux/timer.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>


static const struct snd_soc_dapm_widget sxx_pcm_machine_widgets[] = {

};

static const struct snd_soc_dapm_route sxx_pcm_machine_routes[] = {

};

#define RT5350_DAIFMT (SND_SOC_DAIFMT_NB_NF | \
			SND_SOC_DAIFMT_CBS_CFS) //rt5350 as slave

static int sxx_pcm_machine_init(struct snd_soc_pcm_runtime *rtd)
{


	return 0;
}

static int sxx_pcm_machine_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
    struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	int ret;
    
	ret = snd_soc_dai_set_fmt(cpu_dai, RT5350_DAIFMT);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to set cpu dai format: %d\n", ret);
		return ret;
	}
}

static struct snd_soc_ops sxx_pcm_machine_ops = {
	.hw_params = sxx_pcm_machine_hw_params,
};

static struct snd_soc_dai_link sxx_pcm_machine_dai = {
	.name = "sxx-pcm-machine",
	.stream_name = "sxx-pcm-stream",
    .ops = &sxx_pcm_machine_ops,
	.init = sxx_pcm_machine_init,
	.codec_dai_name = "sxx-pcm-codec",
};

static struct snd_soc_card sxx_pcm_card = {
	.name = "sxx-pcm-machine",
	.owner = THIS_MODULE,
	.dai_link = &sxx_pcm_machine_dai,
	.num_links = 1,

	.dapm_widgets = sxx_pcm_machine_widgets,
	.num_dapm_widgets = ARRAY_SIZE(sxx_pcm_machine_widgets),
	.dapm_routes = sxx_pcm_machine_routes,
	.num_dapm_routes = ARRAY_SIZE(sxx_pcm_machine_routes),
};

static int sxx_pcm_machine_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &sxx_pcm_card;
	int ret;

	card->dev = &pdev->dev;

	sxx_pcm_machine_dai.cpu_of_node = of_parse_phandle(np, "cpu-dai", 0);
	sxx_pcm_machine_dai.codec_of_node = of_parse_phandle(np, "codec-dai", 0);
	sxx_pcm_machine_dai.platform_of_node = sxx_pcm_machine_dai.cpu_of_node;

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
	}
	return ret;
}

static int sxx_pcm_machine_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	snd_soc_unregister_card(card);
	return 0;
}

static const struct of_device_id sxx_pcm_machine_match[] = {
	{ .compatible = "ralink,sxx-pcm-machine" },
	{},
};
MODULE_DEVICE_TABLE(of, sxx_pcm_machine_match);

static struct platform_driver sxx_pcm_machine_driver = {
	.driver		= {
		.name	= "sxx-pcm-machine",
		.owner	= THIS_MODULE,
		.of_match_table = sxx_pcm_machine_match,
	},
	.probe		= sxx_pcm_machine_probe,
	.remove		= sxx_pcm_machine_remove,
};

module_platform_driver(sxx_pcm_machine_driver);

MODULE_AUTHOR("Derek Quan <qdk0901@qq.com>");
MODULE_DESCRIPTION("ALSA SoC Sxx Audio support");
MODULE_LICENSE("GPL v2");
